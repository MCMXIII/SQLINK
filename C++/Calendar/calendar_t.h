#include <map>
#include <string>
#ifndef CALENDAR_T_H
#define CALENDAR_T_H

	using namespace std;
		struct Compare {
  			const bool operator() (const float& a, const float& b) const {return a<b;}
		};
		class Meeting_t {
			public:
				Meeting_t(const float& b, const float& e, const string& s):begin(b),end(e) { if(b < 0 || e >= 24 || b >= e) throw(string("Invalid times for meeting.\n")); subject = s; }
				Meeting_t(const Meeting_t& other):begin(other.begin),end(other.end) { subject = other.subject; }
				~Meeting_t() {}
				const float getBegin() const { return begin; }
				const float getEnd() const { return end; }
				const string getSubject() const { return subject; }
				void setSubject(const string& s) { subject = s; }
			private:
				const float begin;
				const float end;
				string subject;
		};
		class Calendar_t {
			public:
				Calendar_t() {};
				~Calendar_t() {};
				void insert(const Meeting_t* meeting);
				const Meeting_t* remove(const Meeting_t* meeting);
				const Meeting_t* find(const float& hour);
				void clean() {day.clear();}
			private:
				map<float, Meeting_t*, Compare> day;
		};
#endif