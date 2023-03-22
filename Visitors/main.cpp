#define NUMBER_OF_OBJECTS 1000000
//#define TESTING_EMPTY_FUNCTIONS
#include "VariantVisitor.h"
#include "AcyclicVisitor.h"
#include <chrono>
#include <functional>


void test_variant_visitor()
{
	using namespace VariantVisitor;
	std::cout << "Pure testing Variant Visitor\n";
	std::vector<IType> objs{ Type1{}, Type2{}, Type3{} };
	perform_operation_on(objs);
}

void test_acyclic_visitor()
{
	using namespace AcyclicVisitor;
	std::cout << "Pure testing Acyclic Visitor\n";
	std::vector<IType*> objs{ new Type1, new Type2, new Type3 };
	perform_operation_on(objs);

	for (auto&& obj : objs)
	{
		delete obj;
		obj = nullptr;
	}
}

auto measure_time(std::function<void()> pptr)
{
	auto start = std::chrono::steady_clock::now();
	pptr();
	auto end = std::chrono::steady_clock::now();
	auto time1 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	return time1;
}

auto time_test_variant_visitor()
{
	using namespace VariantVisitor;
	std::cout << "Time testing Variant Visitor\n";
	std::vector<IType> objs;
	for (size_t i = 0u; i < NUMBER_OF_OBJECTS; ++i)
	{
		objs.push_back(Type1{});
	}
	auto operation = [&objs]() { perform_operation_on(objs); };
	measure_time(operation);
}

auto time_test_acyclic_visitor()
{
	using namespace AcyclicVisitor;
	std::cout << "Time testing Acyclic Visitor\n";
	std::vector<IType*> objs;
	for (size_t i = 0u; i < NUMBER_OF_OBJECTS; ++i)
	{
		objs.push_back(new Type1);
	}

	auto operation = [&objs]() { perform_operation_on(objs); };
	measure_time(operation);

	for (auto&& obj : objs)
	{
		delete obj;
		obj = nullptr;
	}
}



int main()
{
#ifdef TESTING_EMPTY_FUNCTIONS
	auto time1 = measure_time(&time_test_variant_visitor);
	std::cout << "Time taken: " << time1 << '\n';
	std::cout << "-----------------------------------------\n";
	auto time2 = measure_time(&time_test_acyclic_visitor);
	std::cout << "Time taken: " << time2 << '\n';
#endif // TESTING_EMPTY_FUNCTIONS

#ifndef TESTING_EMPTY_FUNCTIONS
	test_variant_visitor();
	std::cout << "-----------------------------------------\n";
	test_acyclic_visitor();
#endif // !TESTING_EMPTY_FUNCTIONS


	
	return 0;
}