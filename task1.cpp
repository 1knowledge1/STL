#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

struct Student
{
	std::string Name;
	std::string GroupId;
	std::map<std::string, unsigned> Ratings;

	Student(std::string Name, std::map<std::string, unsigned> Ratings) {
		this->Name = Name;
		this->Ratings = Ratings;
	}

	float adv() {
		float summ = 0;
		for (auto i = Ratings.begin(); i != Ratings.end(); ++i) {
			summ += (*i).second;
		}
		return summ / Ratings.size();
	}
	bool bad_result() {
		for (auto i = Ratings.begin(); i != Ratings.end(); ++i) {
			if ((*i).second <= 2) {
				return true;
			}
		}
		return false;
	}
	bool exams_result() {
		bool result = false;
		for (auto i = Ratings.begin(); i != Ratings.end(); ++i) {
			if ((*i).second == 5) result = true;
			else {
				result = false;
				break;
			}
		}
		return result;
	}
	bool excellent_math_score() {
		if (this->Ratings["Math"] == 5) {
			return true;
		}
		return false;
	}

	void get_mark()
	{
		Ratings["Political Since"] = 5;
	}

};

void write(const Student &s) {
	std::cout << s.Name << '\n';
	for (auto it = s.Ratings.begin(); it != s.Ratings.end(); ++it) {
		std::cout << it->first << ":" << it->second << '\n';
	}
	std::cout << '\n' << '\n';
}


int main() {
	Student s1("Ivanov", { { "Math",4 },{ "Political Since",2 },{ "English",5 } }),
			s2("Petrov", { { "Math",5 },{ "Political Since",3 },{ "English",5 } }),
			s3("Sidorov", { { "Math",3 },{ "Political Since",5 },{ "English",5 } });
	std::vector<Student> students{ s1, s2, s3 };

	std::cout << "\t#1" << '\n' << "------------------\n";
	std::sort(students.begin(), students.end(), [](const Student a, const Student b) {
		return (a.Name.compare(b.Name)<0);
	});
	std::for_each(students.begin(), students.end(), write);

	std::cout << "\t#2" << '\n' << "------------------\n";
	std::sort(students.begin(), students.end(), [](Student a, Student b) {
		return (a.adv() > b.adv());
	});
	std::for_each(students.begin(), students.end(), write);

	std::cout << "\t#3" << '\n' << "------------------\n";
	unsigned long c = 0;
	c = std::count_if(students.begin(), students.end(), [](Student a) {
		return (a.bad_result());
	});
	std::cout << c << '\n';

	std::cout << "\t#4" << '\n' << "------------------\n";
	unsigned long a = 0;
	a = std::count_if(students.begin(), students.end(), [](Student a) {
		return (a.exams_result());
	});
	std::cout << a << '\n';

	std::cout << "\t#5" << '\n' << "------------------\n";
	std::vector<Student> target;
	std::copy_if(students.begin(), students.end(), std::back_inserter(target), [](Student a) {
		return a.excellent_math_score();
	});
	std::for_each(target.begin(), target.end(), write);

	std::cout << "\t#6" << '\n' << "------------------\n";
	std::transform(students.begin(), students.end(), students.begin(), [](Student a) {
		a.get_mark();
		return a;
	});
	std::for_each(students.begin(), students.end(), write);
	return 0;
}
