#pragma once
#include<iostream>
#include"ExpressionTree.h"
#include"Exceptions.h"
#include <stdexcept>
#include"Value.h"
#include"Environment.h"
using namespace std;

class GetLength : public ExpressionTree {
public:
    GetLength(int c, int p) {
        collum = c;
        pos = p;
    }
    pair<int, int> getpos() {
        return pair<int, int>(collum, pos);
    }
    ExpressionTree* getchild(int i) {
        throw runtime_error(type_has_no_children(collum, pos, i, "標準ライブラリ関数"));
    }
    pair<Value*, string> getValue() {
        pair<Value*, string> arg1 = Environments::getvalue("arg1", collum, pos);
        if(arg1.second != "array" && arg1.second != "string") throw runtime_error(invalid_type(collum, pos, "array", arg1.second));
        if(arg1.second == "array") return pair<Value*, string>(new Value((long)arg1.first->a->size()), "integer");
        else return pair<Value*, string>(new Value((long)arg1.first->s->size()/3), "integer");
    }
private:
};

class MakeArray : public ExpressionTree {
public:
    MakeArray(int c, int p) {
        collum = c;
        pos = p;
    }
    pair<int, int> getpos() {
        return pair<int, int>(collum, pos);
    }
    ExpressionTree* getchild(int i) {
        throw runtime_error(type_has_no_children(collum, pos, i, "標準ライブラリ関数"));
    }
    pair<Value*, string> getValue() {
        pair<Value*, string> arg1 = Environments::getvalue("arg1", collum, pos);
        if(arg1.second != "integer") throw runtime_error(invalid_type(collum, pos, "integer", arg1.second));

        vector<pair<Value*, string> >* result = new vector<pair<Value*, string> >(arg1.first->i);
        return pair<Value*, string>(new Value(result), "array");
    }
private:
};

class MakeString : public ExpressionTree {
public:
    MakeString(int c, int p) {
        collum = c;
        pos = p;
    }
    pair<int, int> getpos() {
        return pair<int, int>(collum, pos);
    }
    ExpressionTree* getchild(int i) {
        throw runtime_error(type_has_no_children(collum, pos, i, "標準ライブラリ関数"));
    }
    pair<Value*, string> getValue() {
        pair<Value*, string> arg1 = Environments::getvalue("arg1", collum, pos);
        if(arg1.second != "integer") throw runtime_error(invalid_type(collum, pos, "integer", arg1.second));

        string* result = new string(arg1.first->i*3, '\0');
        return pair<Value*, string>(new Value(result), "string");
    }
private:
};

class PushElm : public ExpressionTree {
public:
    PushElm(int c, int p) {
        collum = c;
        pos = p;
    }
    pair<int, int> getpos() {
        return pair<int, int>(collum, pos);
    }
    ExpressionTree* getchild(int i) {
        throw runtime_error(type_has_no_children(collum, pos, i, "標準ライブラリ関数"));
    }
    pair<Value*, string> getValue() {
        pair<Value*, string> arg1 = Environments::getvalue("arg1", collum, pos);
        pair<Value*, string> arg2 = Environments::getvalue("arg2", collum, pos);
        if(arg1.second != "array" && arg1.second != "string") throw runtime_error(invalid_type(collum, pos, "array", arg1.second));
        if(arg1.second == "array") {
            arg1.first->a->push_back(arg2);
            return arg1;
        }
        else {
            arg1.first->s->append(*(arg2.first->s));
            return arg1;
        }
    }
private:
};

class Print : public ExpressionTree {
public:
    Print(int c, int p) {
        collum = c;
        pos = p;
    }
    pair<int, int> getpos() {
        return pair<int, int>(collum, pos);
    }
    ExpressionTree* getchild(int i) {
        throw runtime_error(type_has_no_children(collum, pos, i, "標準ライブラリ関数"));
    }
    pair<Value*, string> getValue() {
        pair<Value*, string> arg1 = Environments::getvalue("arg1", collum, pos);
        if(arg1.second == "integer") cout << arg1.first->i;
        else if(arg1.second == "float") cout << arg1.first->f;
        else if(arg1.second == "string") {
            string msg = *(arg1.first->s);
            cout << msg;
        }
        else if(arg1.second == "array") cout << "array(" << arg1.first->a << ")";
        else if(arg1.second == "function") cout << "function(" << arg1.first->fun << ")";
        else if(arg1.second == "object") cout << "object(" << arg1.first->obj << ")";
        return arg1;
    }
private:
};

class Copy : public ExpressionTree {
public:
    Copy(int c, int p) {
        collum = c;
        pos = p;
    }
    pair<int, int> getpos() {
        return pair<int, int>(collum, pos);
    }
    ExpressionTree* getchild(int i) {
        throw runtime_error(type_has_no_children(collum, pos, i, "標準ライブラリ関数"));
    }
    pair<Value*, string> getValue() {
        pair<Value*, string> arg1 = Environments::getvalue("arg1", collum, pos);
        if(arg1.second == "integer") return pair<Value*, string>(new Value(arg1.first->i), "integer");
        else if(arg1.second == "float") return pair<Value*, string>(new Value(arg1.first->f), "float");
        else if(arg1.second == "string") {
            string* newstr = new string(*arg1.first->s);
            return pair<Value*, string>(new Value(newstr), "string");
        }
        else if(arg1.second == "array") {
            vector<pair<Value*, string> >* newarr = new vector<pair<Value*, string> >(*arg1.first->a);
            return pair<Value*, string>(new Value(newarr), "array");
        }
        else if(arg1.second == "function") {
            Func* newfun = new Func(arg1.first->fun->args, arg1.first->fun->code);
            return pair<Value*, string>(new Value(newfun), "function");
        }
        else if(arg1.second == "object") {
            unordered_map<string, pair<Value*, string> >* newobj =
                new unordered_map<string, pair<Value*, string> >();
            for(auto moto : *arg1.first->obj) {
                (*newobj)[moto.first] = make_pair(new Value(*moto.second.first), moto.second.second);
            }
            return pair<Value*, string>(new Value(newobj), "object");
        }
        return arg1;
    }
private:
};

class Input : public ExpressionTree {
public:
    Input(int c, int p) {
        collum = c;
        pos = p;
    }
    pair<int, int> getpos() {
        return pair<int, int>(collum, pos);
    }
    ExpressionTree* getchild(int i) {
        throw runtime_error(type_has_no_children(collum, pos, i, "標準ライブラリ関数"));
    }
    pair<Value*, string> getValue() {
        pair<Value*, string> arg1 = Environments::getvalue("arg1", collum, pos);
        if(arg1.second != "string") throw runtime_error(invalid_type(collum, pos, "string", arg1.second));

        pair<Value*, string> res;
        if(*(arg1.first->s) == "整数") {
            res = make_pair(new Value(0l), "integer");
            cin >> res.first->i;
            res.second = "integer";
        }
        else if(*(arg1.first->s) == "小数") {
            res = make_pair(new Value(0.0f), "float");
            cin >> res.first->f;
            res.second = "float";
        }
        else if(*(arg1.first->s) == "文字列") {
            res = make_pair(new Value(new string("")), "string");
            cin >> *(res.first->s);
            res.second = "string";
        }
        else throw runtime_error(invalid_type(collum, pos, "", *(arg1.first->s)));
        return res;
    }
private:
};
