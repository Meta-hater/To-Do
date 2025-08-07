#include <iostream>
#include <map>
#include <string>
#include <functional>

static size_t ID;

bool my_is_digit(std::string s) {
	if (s[0] == '0') {
		return false;
	}
	for (const auto& ch : s) {
		if (!isdigit(ch)) {
			return false;
		}
	}

	try {
		long long x = static_cast<long long>(std::stoi(s));
		if (x > LLONG_MAX) {
			return false;
		}
		else {
			return true;
		}
	}
	catch (std::out_of_range) {
		return false;
	}
}

void clear() {
	std::system("cls");
}

// OK 
void print_to_do(std::map<size_t, std::pair<std::string, bool>> lst) {
	size_t mx_task_name_len = 0, mx_id_len = 0, mx_stat_len = 0;
	if (lst.empty()) {
		mx_id_len = 2;
	}

	for (const auto& el : lst) {
		mx_task_name_len = std::max(el.second.first.size(), mx_task_name_len);
		mx_id_len = std::max(std::to_string(el.first).size(), mx_id_len);
		if (el.second.second == 0) {
			mx_stat_len = 8;
		}
	}
	mx_stat_len = std::max(6, static_cast<int>(mx_stat_len));
	mx_task_name_len = std::max(static_cast<int>(mx_task_name_len), 9);

	std::function<void(size_t, char c)> foo;
	foo = [](size_t a, char c = ' ') {
		for (size_t i = 0; i != a; ++i) {
			std::cout << c;
		}
	};

	int vyravnivanie = std::max(9, static_cast<int>(mx_task_name_len)) - std::min(9, static_cast<int>(mx_task_name_len)) + 2;
	
	foo(5, '\t'); std::cout << "+"; foo(mx_id_len + mx_stat_len + mx_task_name_len + 14, '-'); std::cout << "+\n";
	foo(5, '\t'); std::cout << "|"; foo(2, ' '); std::cout << "ID"; foo(mx_id_len, ' '); std::cout << "|";
	foo(2, ' '); std::cout << "Task name"; foo(vyravnivanie, ' '); std::cout << "|";
	foo(2, ' '); std::cout << "Status"; foo(mx_stat_len - 4, ' '); std::cout << "|\n";
	foo(5, '\t'); std::cout << "+"; foo(mx_id_len + mx_stat_len + mx_task_name_len + 14, '-'); std::cout << "+\n";
	
	// строка с тасками
	for (const auto& el : lst) {
				
		size_t id_len = std::to_string(el.first).size();
		size_t task_len = el.second.first.size();

		foo(5, '\t'); std::cout << "|"; foo(2, ' '); std::cout << el.first; foo(mx_id_len - id_len + 2, ' '); std::cout << "|";
		foo(2, ' '); std::cout << el.second.first; foo(mx_task_name_len - task_len + 2, ' '); std::cout << "|";

		foo(2, ' ');
		std::string stat = "Done";
		if (!el.second.second) {
			stat = "Not " + stat;
		}
		std::cout << stat; foo(mx_stat_len - stat.size() + 2, ' '); std::cout << "|\n";
		foo(5, '\t'); std::cout << "+"; foo(mx_id_len + mx_stat_len + mx_task_name_len + 14, '-'); std::cout << "+\n";
	}

} 
// OK
void print_main_menu(std::map<size_t, std::pair<std::string, bool>> lst) { 
	std::function<void(size_t a, char c)> foo =
		[](size_t a, char c) {
		for (size_t i = 0; i != a; ++i) {
			std::cout << c;
		}
		};
	foo(6, '\t'); std::cout << "Hello! This is your To-do list\n";
	print_to_do(lst);
	foo(2, '\n'); foo(2, '\t');
	std::cout << "Here are instructions to use your To-do :)\n";
	foo(2, '\t');
	foo(20, '=');
	foo(2, '\t'); std::cout << "\n";
	foo(2, '\t'); std::cout << "1. Add task\n";
	foo(2, '\t'); std::cout << "2. Delete task\n";
	foo(2, '\t'); std::cout << "3. Edit Task\n";
	foo(2, '\t'); std::cout << "4. Change task status\n";
	foo(2, '\t'); std::cout << "5. Exit to-do\n";
	foo(2, '\t'); foo(20, '=');
	foo(2, '\n');
	foo(2, '\t');
	std::cout << "Enter your command: ";
} 
// OK
void add_task (std::map<size_t, std::pair<std::string, bool>>& lst) {
	clear();
	print_to_do(lst);
	std::cout << "\n\t\tChose task name you want to add: ";
	std::string name; std::getline(std::cin, name);
	ID++;
	lst[ID] = { name, false };
	clear();
	print_to_do(lst);
	std::cout << "\t\tHere is your new to-do!\n\t\tPress <y> to save changes and <n> to reset changes: ";
	std::string c = "smth";

	while (1) {
		std::getline(std::cin, c);
		if (c != "n" && c != "y") {
			std::cout << "\t\tSorry, your command is incorrect, please try again!\n\t\tPress <y> to save changes and <n> to reset changes: ";
		}
		else {
			break;
		}
	}
	
	if (c == "n") {
		lst.erase(ID);
		ID--;
		clear();
		add_task(lst);
	}
	
	else {
		clear();
		print_main_menu(lst);
	}

} 
// OK
void delete_task(std::map<size_t, std::pair<std::string, bool>>& lst) {
	clear();

	if (lst.empty()) {
		std::cout << "\t\tYou have no tasks to delete :c\n\t\tPress Enter to leave: ";
		std::string s;
		while (1) {
			std::getline(std::cin, s);
			if (s.empty()) {
				clear();
				print_main_menu(lst);
				return;
			}
			else {
				std::cout << "\t\tYou have no tasks to delete :c\n\t\tPress Enter to leave: ";
			}
		}
	}

	print_to_do(lst);
	std::cout << "\t\tChoose ID of task you would like to delete: ";
	std::string num;
	size_t old_id;
	while (1) {
		std::getline(std::cin, num);
		if (my_is_digit(num)) {
			old_id = std::stoi(num);
			if (lst.find(old_id) == lst.end()) {
				std::cout << "\t\tNo such ID in to-do, please try again!\n\t\tChoose ID of task you would like to delete: ";
				continue;
			}
			else {
				break;
			}
		}
		else {
			std::cout << "\t\tSorry, your ID is invalid, please try again!\n\t\tChoose ID of task you would like to delete: ";
		}
	}
	std::pair<std::string, bool> old_pair = lst[old_id];
	for (size_t i = old_id; i != lst.size(); ++i) {
		lst[i] = lst[i + 1];
	}
	lst.erase(lst.size());
	clear();
	print_to_do(lst);
	std::cout << "OLD ID - " << old_id << "\n" << "OLD PAIR - " << old_pair.first << " | " << old_pair.second << "\n";
	std::cout << "\t\tHere is your new to-do!\n\t\tPress <y> to save changes and <n> to reset changes: ";
	std::string c = "smth";
	while (1) {
		std::getline(std::cin, c);
		if (c != "n" && c != "y") {
			std::cout << "\t\tSorry, your command is incorrect, please try again!\n\t\tPress <y> to save changes and <n> to reset changes: ";
		}
		else {
			break;
		}
	}

	if (c == "n") {		
		for (size_t i = lst.size(); i >= old_id; --i) {
			lst[i + 1] = lst[i];
		}
		lst[old_id] = old_pair;
		delete_task(lst);
	}
	else if(c == "y") {
		ID--;
		clear();
		print_main_menu(lst);
		return;
	}
	else
	{
		std::cout << "\t\tSorry, your command is incorrect, please try again!\n\t\tPress <y> to save changes and <n> to reset changes: ";
		std::getline(std::cin, c);
	}

}
// OK
void edit_task(std::map<size_t, std::pair<std::string, bool>>& lst) {
	clear();
	if (lst.empty()) {
		std::cout << "\t\tYou have nothing to change :c\n\t\tPress Enter to leave: ";
		std::string s;
		while (1) {
			std::getline(std::cin,s);
			if (s.empty()) {
				clear();
				print_main_menu(lst);
				return;
			}
			else {
				std::cout << "\t\tYou have nothing to change :c\n\t\tPress Enter to leave: ";
			}
		}
	}
	print_to_do(lst);
	std::cout << "\t\tPlease enter task id you would like to change: ";
	std::string id = "smth";
	while (id < "0" || id > "9") {
		std::getline(std::cin, id);
		if (id >= "1" && id <= "9") {
			break;
		}
		else {
			std::cout << "\t\tSorry, your command is incorrect, please try again!\n\t\tChoose ID of task you would like to delete: ";
		}
	}
	clear();
	size_t task_id = std::stoi(id);
	print_to_do(lst);
	std::cout << "\t\tWrite a new name for the task: ";
	std::string old_task_name = lst[task_id].first;
	std::string new_name; std::getline(std::cin, new_name);
	bool status = lst[task_id].second;
	lst[task_id] = { new_name, status };
	clear();
	print_to_do(lst);
	std::cout << "\t\tHere is your new to-do!\n\t\tPress <y> to save changes and <n> to reset changes: ";
	std::string c = "smth";
	while (1) {
		std::getline(std::cin, c);
		if (c != "n" && c != "y") {
			std::cout << "\t\tSorry, your command is incorrect, please try again!\n\t\tPress <y> to save changes and <n> to reset changes: ";
		}
		else {
			break;
		}
	}
	if (c == "n") {
		lst[task_id] = {old_task_name, status};
		edit_task(lst);
	}
	else {
		clear();
		print_main_menu(lst);
		return;
	}
}

void change_task_status(std::map<size_t, std::pair<std::string, bool>>& lst) {
	clear();

	if (lst.empty()) {
		std::cout << "\t\tYou have no tasks to change status :c\n\t\tPress Enter to leave: ";
		std::string s;
		while (1) {
			std::getline(std::cin, s);
			if (s.empty()) {
				clear();
				print_main_menu(lst);
				return;
			}
			else {
				std::cout << "\t\tYou have no tasks to change status :c\n\t\tPress Enter to leave: ";
			}
		}
	}

	print_to_do(lst);
	std::cout << "\t\tChoose ID of task you would like to to change status:  ";
	std::string num;
	size_t id;
	while (1) {
		std::getline(std::cin, num);
		if (my_is_digit(num)) {
			id = std::stoi(num);
			if (lst.find(id) == lst.end()) {
				std::cout << "\t\tNo such ID in to-do, please try again!\n\t\tChoose ID of task you would like to change status: ";
			}
			else {
				break;
			}
		}
		else {
			std::cout << "\t\tSorry, your ID is invalid, please try again!\n\t\tChoose ID of task you would like to change status: ";
		}
	}
	std::cout << "Jumped here\n";
	bool old_stat = lst[id].second;
	clear();
	print_to_do(lst);
	std::cout << "\t\tWrite <1> if you want to mark task as Done. Write <0> if you want to mark task as Not Done: ";
	std::string stat = "smth";
	while (stat != "0" || stat != "1") {
		std::getline(std::cin, stat);
		if (stat == "0" || stat == "1") {
			break;
		}
		else {
			std::cout << "\t\tSorry, your command is incorrect, please try again!\n\t\tChoose ID of task you would like to delete: ";
		}
	}
	if (stat == "0") {
		lst[id].second = false;
	}
	else {
		lst[id].second = true;
	}
	
	clear();
	print_to_do(lst);
	std::cout << "\t\tHere is your new to-do!\n\t\tPress <y> to save changes and <n> to reset changes: ";
	std::string c = "smth";
	while (1) {
		std::getline(std::cin, c);
		if (c != "n" && c != "y") {
			std::cout << "\t\tSorry, your command is incorrect, please try again!\n\t\tPress <y> to save changes and <n> to reset changes: ";
		}
		else {
			break;
		}
	}
	if (c == "n") {
		lst[id].second = old_stat;
		change_task_status(lst);
	}
	else {
		clear();
		print_main_menu(lst);
		return;
	}
}

int main() {
	std::map<size_t, std::pair<std::string, bool>> to_do;

	print_main_menu(to_do);
	std::string command;
	while (1) {
		std::getline(std::cin, command);
		if (command == "5") {
			clear();
			break;
		}
		else if (command == "4") {
			change_task_status(to_do);
		}
		else if (command == "3") {
			edit_task(to_do);
		}
		else if (command == "2") {
			delete_task(to_do);
		}
		else if (command == "1") {
			add_task(to_do);
		}
		else {
			std::cout << "\t\tSorry, I don't understand your command :(\n\t\tPlease choose commands from the list above :)\n\t\tEnter your command: ";
		}
	}
	return 0;

}
