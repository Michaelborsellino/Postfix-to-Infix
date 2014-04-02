#ifndef BET_H
#define BET_H

#include<iostream>
#include<string>
#include<stack>
#include<vector>

class BET{
	private:
		struct BinaryNode{
      			std::string data;
			BinaryNode * left;
			BinaryNode * right;
 BinaryNode(const std::string & d = std::string{}, BinaryNode *p = nullptr, BinaryNode *n = nullptr)
            		: data{d}, left{p}, right{n} {}
 BinaryNode(std::string && d, BinaryNode *p = nullptr, BinaryNode *n = nullptr)
            		: data{std::move(d)}, left{p}, right{n} {}
		};

	public:
		BET();
		BET(const std::string);
		BET(const BET&);
		~BET();
		bool buildFromPostfix(const std::string postfix);
		const BET& operator=(const BET&);
		void printInfixExpression();
		void printPostfixExpression();
		size_t size();
		size_t leaf_nodes();
		bool empty();
	private:
		void printInfixExpression(BinaryNode *n);
		void makeEmpty(BinaryNode *&t);
		BinaryNode * clone(BinaryNode*t)const;
		void printPostfixExpression(BinaryNode *n);
		size_t size(BinaryNode *t);
		size_t leaf_nodes(BinaryNode *t);
		BinaryNode * rootnode;
		
                
};

#include "bet.cpp"
#endif
