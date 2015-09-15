
#include <inttypes.h>

#define tl_second 0
#define tl_minute 1
#define tl_hour   2
#define tl_day    3
#define tl_month  4
#define tl_year   5

class TKeeper
{
public:
    struct location
    {
        float latitude;
        float longitude;
    };

    TKeeper(location & loc, int tz);

    // configuration
    bool setLocation(float, float);
    bool setTimezone(int & );
    bool setDstRules(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t);

    // Political
    void GMT(uint8_t *);
    void DST(uint8_t *);

    //Solar & Astronomical
    bool SunRise(uint8_t *);
    bool SunSet(uint8_t *);
    float MoonPhase(uint8_t *);
    void Sidereal(uint8_t *, bool);
    uint8_t Season(uint8_t *);

    // Utility
    uint8_t DayOfWeek(uint8_t *);
    uint8_t LengthOfMonth(uint8_t *);
    bool IsLeapYear(int);

private:
    location m_location;
    int m_tz;

    uint8_t dstm1, dstw1, dstm2, dstw2, dstadv;
    void Adjust(uint8_t *, long);
    bool ComputeSun(uint8_t *, bool);
    char Signum(int);
    int Absolute(int);
    long DayNumber(uint16_t, uint8_t, uint8_t);
    bool InDst(uint8_t *);
    uint8_t getSeason(uint8_t *);

    static const float MOON_PERIOD;
};
