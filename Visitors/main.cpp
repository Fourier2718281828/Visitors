#define NUMBER_OF_OBJECTS 1000000
#define NO_TIME_MEASURING
#include "VariantVisitor.h"
#include "AcyclicVisitor.h"
#include "CommonVisitor.h"
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

void test_common_visitor()
{
	using namespace CommonVisitor;
	std::cout << "Pure testing Common Visitor\n";
	std::vector<IType*> objs{ new Type1, new Type2, new Type3 };
	perform_operation_on(objs);

	for (auto&& obj : objs)
	{
		delete obj;
		obj = nullptr;
	}
}

auto measure_time(std::function<void()> measurable)
{
	auto start = std::chrono::steady_clock::now();
	measurable();
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

auto time_test_common_visitor()
{
	using namespace CommonVisitor;
	std::cout << "Time testing Common Visitor\n";
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
	/*
	* To switch to "measure-time"-mode, uncomment "#define NO_TIME_MEASURE"
	* Or add it manualy ABOVE all the includes in this file
	*/
#ifdef NO_TIME_MEASURING
	auto time1 = measure_time(&time_test_variant_visitor);
	std::cout << "Time taken: " << time1 << "ms" << '\n';
	std::cout << "-----------------------------------------\n";
	auto time3 = measure_time(&time_test_common_visitor);
	std::cout << "Time taken: " << time3 << "ms" << '\n';
	std::cout << "-----------------------------------------\n";
	auto time2 = measure_time(&time_test_acyclic_visitor);
	std::cout << "Time taken: " << time2 << "ms" << '\n';
#endif // TESTING_EMPTY_FUNCTIONS

	/*
	* To switch to "no-measure-time"-mode, comment "#define NO_TIME_MEASURE"
	* Or remove it manualy from ABOVE all the includes in this file
	*/
#ifndef NO_TIME_MEASURING
	test_common_visitor();
	std::cout << "-----------------------------------------\n";
	test_variant_visitor();
	std::cout << "-----------------------------------------\n";
	test_acyclic_visitor();
#endif // !TESTING_EMPTY_FUNCTIONS
	
	return 0;
}