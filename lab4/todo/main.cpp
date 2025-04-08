#include <algorithm>
#include <chrono>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Task {
   private:
    std::string m_name;
    std::string m_description;
    std::chrono::system_clock::time_point m_created;
    std::chrono::system_clock::time_point m_due;

   public:
    Task(std::string name, std::string description, auto created, auto due)
        : m_name(std::move(name)),
          m_description(std::move(description)),
          m_created(created),
          m_due(due) {};
    Task(std::string name, std::string description)
        : m_name(std::move(name)),
          m_description(std::move(description)),
          m_created(std::chrono::system_clock::now()) {};
    Task(std::string name, std::string description, auto due)
        : m_name(std::move(name)),
          m_description(std::move(description)),
          m_created(std::chrono::system_clock::now()),
          m_due(due) {};

    [[nodiscard]] std::string getName() const { return m_name; }
    void setName(const std::string& name) { m_name = name; }

    [[nodiscard]] std::string getDescription() const { return m_description; }
    void setDescription(const std::string& description) { m_description = description; }

    [[nodiscard]] auto getCreated() const { return m_created; }
    void setCreated(auto created) { m_created = created; }

    [[nodiscard]] auto getDue() const { return m_due; }
    void setDue(auto due) { m_due = due; }

    [[nodiscard]] std::string toCSV() const {
        std::string created_dur = std::to_string(
            std::chrono::duration_cast<std::chrono::seconds>(m_created.time_since_epoch()).count());
        std::string due_dur = std::to_string(
            std::chrono::duration_cast<std::chrono::seconds>(m_due.time_since_epoch()).count());

        return m_name + "," + m_description + "," + created_dur + "," + due_dur;
    }

    static Task fromCSV(const std::string csv) {
        std::istringstream ss(csv);
        std::string name, description;
        std::string created_dur, due_dur;

        std::getline(ss, name, ',');
        std::getline(ss, description, ',');
        std::getline(ss, created_dur, ',');
        std::getline(ss, due_dur);
        auto created = std::chrono::system_clock::from_time_t(std::stoi(created_dur));
        auto due = std::chrono::system_clock::from_time_t(std::stoi(due_dur));

        return {name, description, created, due};
    }

    bool operator==(const Task& other) const { return m_name == other.m_name; }
};

static void saveTasksToFile(const std::vector<Task>& tasks, const std::string& filepath) {
    std::ofstream file(filepath);

    if (file.is_open()) {
        for (const Task& task : tasks) {
            file << task.toCSV() << '\n';
        }
        file.close();
    } else {
        std::cerr << "Failed to open the storage file!\n";
    }
}

static std::vector<Task> loadTasksFromFile(const std::string& filepath) {
    std::vector<Task> tasks;

    std::ifstream file(filepath);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            tasks.emplace_back(Task::fromCSV(line));
        }
        file.close();
    } else {
        std::cerr << "Failed to open the storage file!\n";
    }
    return tasks;
}

static void addTask(const Task& task, std::vector<Task>& tasks, const std::string& filepath) {
    tasks.emplace_back(task);
    saveTasksToFile(tasks, filepath);
}

static void removeTask(const Task& task, std::vector<Task>& tasks, const std::string& filepath) {
    auto it = std::ranges::find(tasks, task);
    if (it != tasks.end()) {
        tasks.erase(it);
    }
    saveTasksToFile(tasks, filepath);
}

static void writeTasks(const std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks available.\n";
        return;
    }
    std::cout << "======= Task List =======\n";
    for (const auto& task : tasks) {
        std::time_t created = std::chrono::system_clock::to_time_t(task.getCreated());
        auto due_raw = task.getDue();
        std::cout << "Task: " << task.getName() << "\n"
                  << "Description: " << task.getDescription() << "\n"
                  << "Created: " << std::put_time(std::localtime(&created), "%Y-%m-%d %H:%M:%S")
                  << "\n";
        if (due_raw == std::chrono::system_clock::time_point{}) {
            std::cout << "No due time!\n";
        } else {
            std::time_t due = std::chrono::system_clock::to_time_t(due_raw);
            std::cout << "Due: " << std::put_time(std::localtime(&due), "%Y-%m-%d %H:%M:%S")
                      << "\n";
        }
        std::cout << "-----------------------------------\n";
    }
}

int main(int argc, char* argv[]) {
    std::filesystem::path storagePath = std::filesystem::canonical(argv[0]).parent_path();
    std::string doneStorage = storagePath.string() + "/storage/done";
    std::string pendingStorage = storagePath.string() + "/storage/pending";

    std::vector<Task> done;
    std::vector<Task> pending;

    pending = loadTasksFromFile(pendingStorage);
    done = loadTasksFromFile(doneStorage);

    if (pending.size() == 0) {
        addTask({"First task!", "This is the first task"}, pending, pendingStorage);
        addTask({"Secondshow task!", "This is the second task with due date",
                 std::chrono::system_clock::now() + std::chrono::hours(10)},
                pending, pendingStorage);
    }
    std::cout << "------ Pending tasks ------\n";
    writeTasks(pending);

    bool running = true;
    while (running) {
        std::cout
            << "Possible commands:\nshow: shows all tasks\nadd: adds a task\ndone: finishes a "
               "task\nremove: removes "
               "a task\nEnter your command: \n";
        std::string command;
        std::cin >> command;
        if (command == "add") {
            std::cout << "Enter the name: ";
            std::string name;
            std::cin >> name;
            std::cout << "Enter the description: ";
            std::string description;
            std::cin >> description;
            std::cout << "Enter the deadline (in hours, 0 is no deadline): ";
            std::string deadline;
            std::cin >> deadline;
            if (std::stoi(deadline) == 0) {
                addTask(Task(name, description), pending, pendingStorage);
            } else {
                addTask(Task(name, description,
                             std::chrono::system_clock::now() +
                                 std::chrono::hours(std::stoi(deadline))),
                        pending, pendingStorage);
            }
        }
        if (command == "done") {
            std::cout << "Enter the name: ";
            std::string name;
            std::cin >> name;
            auto it = std::ranges::find(pending, Task(name, ""));

            if (it != pending.end()) {
                Task temp = *it;
                addTask(temp, done, doneStorage);
                removeTask(temp, pending, pendingStorage);
            }
        }
        if (command == "remove") {
            std::cout << "Enter the name: ";
            std::string name;
            std::cin >> name;
            removeTask(Task(name, ""), pending, pendingStorage);
            removeTask(Task(name, ""), done, doneStorage);
        }
        if (command == "show") {
            std::cout << "------ Pending tasks ------\n";
            writeTasks(pending);
            std::cout << "------ Done tasks ------\n";
            writeTasks(done);
        }
        std::cout << "\n\n";
    }
}