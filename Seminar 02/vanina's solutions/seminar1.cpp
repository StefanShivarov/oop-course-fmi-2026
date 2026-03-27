 #include<iostream>
 #include<fstream>

 using std::cin;
 using std::cout;
 using std::endl;

 class Time {
 private:
     int hour_ = 0;
     int minute_ = 0;
     int second_ = 0;

 public:
     void setHour(const int hour) {
         if (hour < 0 || hour > 23) {
             cout << "Invalid input" << endl;
             return;
         }
         this->hour_ = hour;
     }

     void setMinute(const int minute) {
         if (minute < 0 || minute > 59) {
             cout << "Invalid input" << endl;
             return;
         }
         this->minute_ = minute;
     }

     void setSecond(const int second) {
         if (second < 0 || second > 59) {
             cout << "Invalid input" << endl;
             return;
         }
         this->second_ = second;
     }

     int getHour() const {
         return this->hour_;
     }

     int getMinute() const {
         return this->minute_;
     }

     int getSecond() const {
         return this->second_;
     }

     long toSeconds() const {
         return (hour_ * 3600 + minute_ * 60 + second_);
     }

     void addSeconds(const int delta) {
         second_ += delta;
         while (second_ > 59) {
             minute_++;
             second_ -= 60;
         }
         while (minute_ > 59) {
             hour_++;
             minute_ -= 60;
         }
         if (hour_ > 23) {
             hour_ -= 24;
         }
     }

     bool isBefore(const Time &other) const {
         return toSeconds() < other.toSeconds();
     }

     bool isAfter(const Time &other) const {
         return toSeconds() > other.toSeconds();
     }

     bool write(std::ostream &os) const {
         os << hour_ << ":" << minute_ << ":" << second_ << endl;
         return true;
     }


     void print() const {
         cout << hour_ << ":" << minute_ << ":" << second_ << endl;
     }
 };

 int main() {
     Time time;
     time.setHour(23);
     time.setMinute(59);
     time.setSecond(59);
     time.print();
     time.addSeconds(2);
     time.print();
     return 0;
 }
