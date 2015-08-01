class DateTime {
    public:
        DateTime (long t =0);
        DateTime (uint16_t year, uint8_t month, uint8_t day,
                uint8_t hour =0, uint8_t min =0, uint8_t sec =0);
        DateTime (const char* date, const char* time);

        uint16_t year() const       { return 2000 + yOff;  }
        uint8_t month() const       { return m;  }
        uint8_t day() const         { return d;  }
        uint8_t hour() const        { return hh;  }
        uint8_t minute() const      { return mm;  }
        uint8_t second() const      { return ss;  }
        uint8_t dayOfWeek() const;
        // 32-bit times as seconds since 1/1/2000
        long get() const;
    protected:
        uint8_t yOff, m, d, hh, mm, ss;
};

class Rtc
{
public:
    Rtc();
    ~Rtc();
    void begin() {}
    void adjust(const DateTime& dt);
    DateTime now();
    uint8_t isrunning();

    // Set IRQ output state: 0=disabled, 1=1Hz, 2=512Hz.
    void setIRQ(uint8_t state);
    // Set IRQ output active state to LOW or HIGH.
    void setIRQLevel(uint8_t level);
    // Sets the calibration value to given value in the range -31 - 31, which
    // corresponds to -126ppm - +63ppm; see table 13 in th BQ32000 datasheet.
    void setCalibration(int8_t value);
    void setCharger(int state);

private:
    uint8_t readRegister(uint8_t address);
    bool writeRegister(uint8_t address, uint8_t value);
    bool writeRegister(uint8_t address, uint8_t * values, uint8_t len);
    uint8_t bcd2bin (uint8_t val) { return val - 6 * (val >> 4);  }
    uint8_t bin2bcd (uint8_t val) { return val + 6 * (val / 10);  }

};
