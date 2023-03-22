#pragma once
#include <iostream>
#include <vector>


namespace AcyclicVisitor
{
	//Visitor abstractions
	template<typename Type>
	class Visitor
	{
	public:
		virtual void visit(const Type* const) const = 0;
	};

	class AbstractVisitor 
	{
	public:
		virtual ~AbstractVisitor() = default;
	};

	class IType
	{
	public:
		virtual ~IType() = default;
	public:
		virtual void accept(AbstractVisitor*) = 0;
	};

	//Hierarchy of types
	class Type1 : public IType 
	{
	public:
		void accept(AbstractVisitor* avisitor) override
		{
			auto visitor = dynamic_cast<Visitor<Type1>*>(avisitor);
			visitor->visit(this);
		}
	};

	class Type2 : public IType 
	{
	public:
		void accept(AbstractVisitor* avisitor) override
		{
			auto* visitor = dynamic_cast<Visitor<Type2>*>(avisitor);
			visitor->visit(this);
		}
	};

	class Type3 : public IType 
	{
	public:
		void accept(AbstractVisitor* avisitor) override
		{
			auto* visitor = dynamic_cast<Visitor<Type3>*>(avisitor);
			visitor->visit(this);
		}
	};


	//Concrete visitor
	class SomeVisitor : public AbstractVisitor
		              , public Visitor<Type1>
		              , public Visitor<Type2>
		              , public Visitor<Type3>
	{
	public:

		void visit(const Type1* const) const override
		{
#ifndef TESTING_EMPTY_FUNCTIONS
			std::cout << "Performing operation on Type1\n";
#endif // EMPTY_OPERATIONS
		}

		void visit(const Type2* const) const override
		{
#ifndef TESTING_EMPTY_FUNCTIONS
			std::cout << "Performing operation on Type2\n";
#endif // EMPTY_OPERATIONS
		}

		void visit(const Type3* const) const override
		{
#ifndef TESTING_EMPTY_FUNCTIONS
			std::cout << "Performing operation on Type3\n";
#endif // EMPTY_OPERATIONS
		};
	};


	void perform_operation_on(const std::vector<IType*>& objs)
	{
		AbstractVisitor* abstract_visitor = new SomeVisitor;

		for (auto&& obj : objs)
		{
			obj->accept(abstract_visitor);
		}

		delete abstract_visitor;
		abstract_visitor = nullptr;
	}
}