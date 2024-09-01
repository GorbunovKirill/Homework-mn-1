#include <iostream>
#include <thread>
#include <chrono>

int client_count = 0;  
bool done = false;  

void client_thread(int max_clients) {
    while (client_count < max_clients) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        client_count++;
        std::cout << "Новый клиент. Текущее количество: " << client_count << std::endl;
    }
    done = true;  
}

void operator_thread() {
    while (!done || client_count > 0) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if (client_count > 0) {
            client_count--;
            std::cout << "Клиент обслужен. Оставшееся количество: " << client_count << std::endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    int max_clients = 10;

    std::thread client(client_thread, max_clients);
    std::thread oper(operator_thread);

 
    client.join();
    oper.join();

    std::cout << "Все клиенты обслужены." << std::endl;

    return 0;
}
