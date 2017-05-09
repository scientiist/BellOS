#include "../../kernel/core/asm/asm.h"
#define RTC_BASE 0x70
#define RTC_DATA 0x71

//
// Return Unix time in seconds, reading current time and date from RTC.
//
// This assumes that RTC is in UTC, which it typically isn't, but since
// the timezone isn't known, just let some process adjust it after boot.
//
unsigned clock_rtc_read() {

    int update = 1; // update in progress flag
    while(update) {
        // check if there's update in progress
        outb(RTC_BASE, 0xA); // RTC register A
        unsigned char c = inb(RTC_DATA);
        if(!(c & 0x80)) {
            update = 0;
        }
    }

    // read the various RTC fields
    
    outb(RTC_BASE, 0);
    unsigned char sec = inb(RTC_DATA);

    outb(RTC_BASE, 2);
    unsigned char min = inb(RTC_DATA);

    outb(RTC_BASE, 4);
    unsigned char hour = inb(RTC_DATA);

    outb(RTC_BASE, 7); // day of month
    unsigned char day = inb(RTC_DATA);

    outb(RTC_BASE, 8);
    unsigned char month = inb(RTC_DATA);

    outb(RTC_BASE, 9); // two digits, we assume 2000-2099
    unsigned char year = inb(RTC_DATA);

    // read RTC register B to figure out how to deal with the data
    outb(RTC_BASE, 0xB);
    unsigned char format = inb(RTC_DATA);

    // convert all fields from BDC to binary if bit[2] is clear
    if(!(format & 0x4)) {

        sec = (sec & 0xf) + (sec>>4)*10;
        min = (min & 0xf) + (min>>4)*10;
        hour = (hour & 0xf) + ((hour&0x70)>>4)*10 + (hour&0x80); // keep bit-7
        day = (day & 0xf) + (day>>4)*10;
        month = (month & 0xf) + (month>>4)*10;
        year = (year & 0xf) + (year>>4)*10;

    }
    
    // convert hours from 12 to 24 format if bit[1] is clear
    if(!(format & 0x2)) {
        int ampm = hour&0x80;
        hour = hour&0x7f;
        // fix 24:00 = 12am oddity
        if(hour == 12) hour = 0;
        if(ampm) hour += 12;
    }

    // Figure out the number of days after the beginning of 2000

    // Our calculation is simplified by the fact that 2000 is a leap year,
    // and after that every 4th year is a leap year, until 2100 before which
    // this routine will have to be updated anyway, because RTC wraps to 00.
    //
    // So first calculate days as if there was no leap years, then add
    // 1 day for each leap year that has passed, and one for leap back in 2000.
    //
    // This will actually give bogus values if year is 2000 (or before that),
    // but for code written in 2007 that shouldn't matter that much...
    //
    unsigned fullyeardays = year * 365 + ((year-1)/4) + 1;

    // Next get the number of (full) days for this year, using the lookup
    // table for months. RTC day and month count from 1. Adjust month.
    // Only adjust day if it's not leap year, or if leap day hasn't passed.
    //
    static unsigned daysbeforemonth[12] // for normal, non-leap year
        = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
    unsigned thisyeardays = daysbeforemonth[month-1] + day
        - (((year%4)==0 && month > 2) ? 0 : 1); // only if no leap day passed

    // Sum days before and during this year to get date, then adjust EPOCH
    // to stay compatible with Unix style 1970-01-01 00:00.
    //
    // The number 10957 was arrived at by first using GNU date:
    //   date -d '2000-01-01 00:00:00 UTC' '+%s' -> 946684800
    // and dividing the result with 24*60*60 to get the number of days.
    //
    unsigned date = fullyeardays + thisyeardays + 10957;


    // Finally build system time, unix format seconds since 1970-01-01 00:00
    unsigned time = sec + 60 * (min + 60 * (hour + 24 * date));

    return time;
    
}