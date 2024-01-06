#ifndef _TIMEHM_H_
#define _TIMEHM_H_
class TimeHM
{
private:
	int hours;
	int minutes;
	int seconds;
public:
	TimeHM();
	TimeHM(int h, int m, int s);
	// Copy constructor
	TimeHM(const TimeHM& t)
		: hours(t.hours), minutes(t.minutes), seconds(t.seconds) {}

	void setHours(int h);
	void setMinutes(int m);
	void setSeconds(int s);

	int getHours() const;
	int getMinutes() const;
	int getSeconds() const;


	void display();

	TimeHM operator+(const TimeHM& t)
	{
		int total_seconds = this->seconds + t.seconds;
		int total_minutes = this->minutes + t.minutes + total_seconds / 60;
		int total_hours = this->hours + t.hours + total_minutes / 60;
		return TimeHM(total_hours, total_minutes % 60, total_seconds % 60);
	}
	TimeHM operator-(const TimeHM& other)
	{
		int h = this->hours - other.hours;
		int m = this->minutes - other.minutes;
		int s = this->seconds - other.seconds;
		if (s < 0) {
			--m;
			s += 60;
		}
		if (m < 0) {
			--h;
			m += 60;
		}
		return TimeHM(h, m, s);
	}
	TimeHM operator=(int s)
	{
		this->seconds = s;
		this->minutes = this->seconds / 60;
		this->hours = this->minutes / 60;

		this->seconds %= 60;
		this->minutes %= 60;
		return *this;
	}
	TimeHM& operator+=(int s)
	{
		this->seconds += s;
		this->minutes += seconds / 60;
		this->hours += minutes / 60;
		this->seconds %= 60;
		this->minutes %= 60;
		return *this;
	}
	TimeHM& operator-=(int s)
	{
		int totalSeconds = hours * 3600 + minutes * 60 + seconds;
		totalSeconds -= s;

		if (totalSeconds < 0) {
			totalSeconds = 0;
		}

		hours = totalSeconds / 3600;
		totalSeconds %= 3600;
		minutes = totalSeconds / 60;
		seconds = totalSeconds % 60;
		return *this;
	}
	TimeHM& operator-=(TimeHM t)
	{
		int totalSeconds = this->hours * 3600 + this->minutes * 60 + this->seconds;
		totalSeconds -= t.getHours() * 3600 + t.getMinutes() * 60 + t.getSeconds();

		if (totalSeconds < 0) {
			totalSeconds = 0;
		}

		hours = totalSeconds / 3600;
		totalSeconds %= 3600;
		minutes = totalSeconds / 60;
		seconds = totalSeconds % 60;
		return *this;
	}
	TimeHM& operator++(int)
	{
		this->seconds++;
		this->minutes += seconds / 60;
		this->hours += minutes / 60;
		this->seconds %= 60;
		this->minutes %= 60;
		return *this;
	}
	/* LOGICAL OPERATORS */
	bool operator==(const TimeHM& t)
	{
		int ourSeconds = this->seconds + this->minutes * 60 + this->hours * 3600;
		int theirSeconds = t.seconds + t.minutes * 60 + t.hours * 3600;
		return (ourSeconds == theirSeconds);
	}
	bool operator>=(const TimeHM& t)
	{
		int ourSeconds = this->seconds + this->minutes * 60 + this->hours * 3600;
		int theirSeconds = t.seconds + t.minutes * 60 + t.hours * 3600;
		return (ourSeconds >= theirSeconds);
	}
	bool operator<=(const TimeHM& t)
	{
		int ourSeconds = this->seconds + this->minutes * 60 + this->hours * 3600;
		int theirSeconds = t.seconds + t.minutes * 60 + t.hours * 3600;
		return (ourSeconds <= theirSeconds);
	}
	bool operator>(const TimeHM& t)
	{
		int ourSeconds = this->seconds + this->minutes * 60 + this->hours * 3600;
		int theirSeconds = t.seconds + t.minutes * 60 + t.hours * 3600;
		return (ourSeconds > theirSeconds);
	}
	bool operator<(const TimeHM& t)
	{
		int ourSeconds = this->seconds + this->minutes * 60 + this->hours * 3600;
		int theirSeconds = t.seconds + t.minutes * 60 + t.hours * 3600;
		return (ourSeconds < theirSeconds);
	}
	/* LOGICAL OPERATORS WITH SECONDS */
	bool operator<=(int durationSeconds) 
	{
		int totalSeconds = this->hours * 3600 + this->minutes * 60 + this->seconds;
		return (totalSeconds <= durationSeconds);
	}
	bool operator>=(int durationSeconds)
	{
		int totalSeconds = this->hours * 3600 + this->minutes * 60 + this->seconds;
		return (totalSeconds >= durationSeconds);
	}
	bool operator>(int durationSeconds)
	{
		int totalSeconds = this->hours * 3600 + this->minutes * 60 + this->seconds;
		return (totalSeconds > durationSeconds);
	}
	bool operator<(int durationSeconds)
	{
		int totalSeconds = this->hours * 3600 + this->minutes * 60 + this->seconds;
		return (totalSeconds < durationSeconds);
	}
	bool operator==(int durationSeconds)
	{
		int totalSeconds = this->hours * 3600 + this->minutes * 60 + this->seconds;
		return (totalSeconds == durationSeconds);
	}

	bool operator!=(int durationSeconds)
	{
		int totalSeconds = this->hours * 3600 + this->minutes * 60 + this->seconds;
		return (totalSeconds != durationSeconds);
	}

	~TimeHM();

};

#endif

