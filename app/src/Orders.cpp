#include <Orders.hpp>

Orders::Orders() {}

Orders::~Orders() {
	UnloadTexture(this->background);
}

void Orders::Update() {
	DrawTexture(this->background, 0, 0, WHITE);
}

Orders::Order Orders::generateOrder() {
    std::chrono::seconds duration(10);
    std::chrono::steady_clock::time_point endTime = this->startTime + duration;
	
	if (std::chrono::steady_clock::now() >= endTime) {
		this->startTime = std::chrono::steady_clock::now();
		endTime = this->startTime + duration;
		std::cout << "Order generated" << std::endl;
	}
    return {};
}