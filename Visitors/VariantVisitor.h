#pragma once
#include <iostream>
#include <variant>
#include <vector>

namespace VariantVisitor
{
	class Type1 {};
	class Type2 {};
	class Type3 {};

	using IType = std::variant<Type1, Type2, Type3>;

	class TypeVisitor
	{
	public:

		void operator()(const Type1&) const
		{
#ifndef NO_TIME_MEASURING
			std::cout << "Variant Visitor: performing operation on Type1\n";
#endif // EMPTY_OPERATIONS
		}

		void operator()(const Type2&) const
		{
#ifndef NO_TIME_MEASURING
			std::cout << "Variant Visitor: performing operation on Type2\n";
#endif // EMPTY_OPERATIONS
		}

		void operator()(const Type3&) const
		{
#ifndef NO_TIME_MEASURING
			std::cout << "Variant Visitor: performing operation on Type3\n";
#endif // EMPTY_OPERATIONS
		}
	};

	void perform_operation_on(const std::vector<IType>& objs)
	{
		for (auto&& obj : objs)
		{
			std::visit(TypeVisitor{}, obj);
		}
	}
}