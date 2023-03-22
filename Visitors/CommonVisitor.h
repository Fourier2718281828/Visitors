#pragma once
#include <iostream>
#include <vector>

namespace CommonVisitor
{
	//Forwarded declarations of types
	class Type1;
	class Type2;
	class Type3;

	//Visitor abstraction
	class IVisitor
	{
	public:
		virtual ~IVisitor() = default;
	public:
		virtual void visit(const Type1* const) const = 0;
		virtual void visit(const Type2* const) const = 0;
		virtual void visit(const Type3* const) const = 0;
	};

	//Type abstraction
	class IType
	{
	public:
		virtual ~IType() = default;
	public:
		virtual void accept(const IVisitor* const) = 0;
	};

	//Hierarchy of concrete types
	class Type1 : public IType
	{
	public:
		void accept(const IVisitor* const visitor) override
		{
			visitor->visit(this);
		}
	};

	class Type2 : public IType
	{
	public:
		void accept(const IVisitor* const visitor) override
		{
			visitor->visit(this);
		}
	};

	class Type3 : public IType
	{
	public:
		void accept(const IVisitor* const visitor) override
		{
			visitor->visit(this);
		}
	};

	//Concrete visitor
	class TypeVisitor : public IVisitor
	{
	public:

		~TypeVisitor() override = default;

	public:
		void visit(const Type1* const) const override
		{
#ifndef NO_TIME_MEASURING
			std::cout << "Common visitor: performing operation on Type1\n";
#endif // EMPTY_OPERATIONS
		}

		void visit(const Type2* const) const override
		{
#ifndef NO_TIME_MEASURING
			std::cout << "Common visitor: performing operation on Type2\n";
#endif // EMPTY_OPERATIONS
		}

		void visit(const Type3* const) const override
		{
#ifndef NO_TIME_MEASURING
			std::cout << "Common visitor: performing operation on Type3\n";
#endif // EMPTY_OPERATIONS
		};
	};

	//Applying Visitor
	void perform_operation_on(const std::vector<IType*>& objs)
	{
		IVisitor* visitor = new TypeVisitor;

		for (auto&& obj : objs)
		{
			obj->accept(visitor);
		}

		delete visitor;
		visitor = nullptr;
	}
}