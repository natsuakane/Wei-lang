#pragma once
#include <exception>
#include<string>
#include<cmath>
#include"ExpressionTree.cpp"
#include"Exceptions.cpp"
#include"Variable.cpp"
#include"Environment.cpp"
#include"Exceptions.cpp"
using namespace std;

class BinaryOperator : public ExpressionTree {
public:
    BinaryOperator(string o, ExpressionTree* e1, ExpressionTree* e2, int c, int p) {
        op = o;
        exp1 = e1;
        exp2 = e2;
        collum = c;
        pos = p;
    }
    pair<int, int> getpos() {
        return pair<int, int>(collum, pos);
    }
    ExpressionTree* getchild(int i) {
        if(i == 0) return exp1;
        if(i == 1) return exp2;
        throw runtime_error(type_has_no_children(collum, pos, i, "二項演算子"));
    }
    pair<Value*, string> getValue();
private:
    string op;
    ExpressionTree* exp1;
    ExpressionTree* exp2;
};

pair<Value*, string> BinaryOperator::getValue() {
    if(op == "乗") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer") {
            return pair<Value*, string>(new Value((long)pow(v1.first->i, v2.first->i)), "integer");
        }
    }
    else if(op == "掛") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer") {
            return pair<Value*, string>(new Value(v1.first->i * v2.first->i), "integer");
        }
    }
    else if(op == "割") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer") {
            return pair<Value*, string>(new Value(v1.first->i / v2.first->i), "integer");
        }
    }
    else if(op == "余") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer") {
            return pair<Value*, string>(new Value(v1.first->i % v2.first->i), "integer");
        }
    }
    else if(op == "足") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer") {
            return pair<Value*, string>(new Value(v1.first->i + v2.first->i), "integer");
        }
    }
    else if(op == "引") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer") {
            return pair<Value*, string>(new Value(v1.first->i - v2.first->i), "integer");
        }
    }
    else if(op == "等") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer") {
            return pair<Value*, string>(new Value((long)(v1.first->i == v2.first->i)), "integer");
        }
    }
    else if(op == "大") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer") {
            return pair<Value*, string>(new Value((long)(v1.first->i > v2.first->i)), "integer");
        }
    }
    else if(op == "小") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer") {
            return pair<Value*, string>(new Value((long)(v1.first->i < v2.first->i)), "integer");
        }
    }
    else if(op == "違") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer") {
            return pair<Value*, string>(new Value((long)(v1.first->i != v2.first->i)), "integer");
        }
    }
    else if(op == "且") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer") {
            return pair<Value*, string>(new Value((long)(v1.first->i && v2.first->i)), "integer");
        }
    }
    else if(op == "或") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer") {
            return pair<Value*, string>(new Value((long)(v1.first->i || v2.first->i)), "integer");
        }
    }
    else if(op == "是") {
        try {
            string name = ((Variable *)exp1)->getname();
            Environments::setvar(name, exp2->getValue());
            return exp2->getValue();
        }
        catch(exception e) { throw runtime_error(invalid_type_assign(collum, pos)); }
    }
    return pair<Value*, string>(nullptr, "");
}