#include "BinaryOperator.h"
#include"Variable.cpp"
#include"Index.cpp"
#include"ObjectIndex.cpp"
#include"Environment.h"

double getfloat(pair<Value*, string> v, int collum, int pos) {
    if(v.second == "integer") return (double)(v.first->i);
    if(v.second == "float") return v.first->f;
    throw runtime_error(invalid_type(collum, pos, "number", v.second));
}

pair<Value*, string> BinaryOperator::getValue() {
    if(op == "乗") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer" && v2.second == "integer") {
            return pair<Value*, string>(new Value((long)pow(v1.first->i, v2.first->i)), "integer");
        }
        else {
            return pair<Value*, string>(new Value(
                pow(getfloat(v1, collum, pos), getfloat(v2, collum, pos))
            ), "float");
        }
    }
    else if(op == "掛") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer" && v2.second == "integer") {
            return pair<Value*, string>(new Value(v1.first->i * v2.first->i), "integer");
        }
        else {
            return pair<Value*, string>(new Value(
                getfloat(v1, collum, pos) * getfloat(v2, collum, pos)
            ), "float");
        }
    }
    else if(op == "割") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer" && v2.second == "integer") {
            return pair<Value*, string>(new Value(v1.first->i / v2.first->i), "integer");
        }
        else {
            return pair<Value*, string>(new Value(
                getfloat(v1, collum, pos) / getfloat(v2, collum, pos)
            ), "float");
        }
    }
    else if(op == "余") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer" && v2.second == "integer") {
            return pair<Value*, string>(new Value(v1.first->i % v2.first->i), "integer");
        }
        else {
            return pair<Value*, string>(new Value(
                fmod(getfloat(v1, collum, pos), getfloat(v2, collum, pos))
            ), "float");
        }
    }
    else if(op == "足") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer" && v2.second == "integer") {
            return pair<Value*, string>(new Value(v1.first->i + v2.first->i), "integer");
        }
        else {
            return pair<Value*, string>(new Value(
                getfloat(v1, collum, pos) + getfloat(v2, collum, pos)
            ), "float");
        }
    }
    else if(op == "引") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer" && v2.second == "integer") {
            return pair<Value*, string>(new Value(v1.first->i - v2.first->i), "integer");
        }
        else {
            return pair<Value*, string>(new Value(
                getfloat(v1, collum, pos) - getfloat(v2, collum, pos)
            ), "float");
        }
    }
    else if(op == "等") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer" && v2.second == "integer") {
            return pair<Value*, string>(new Value((long)(v1.first->i == v2.first->i)), "integer");
        }
        else {
            return pair<Value*, string>(new Value(
                (long)(getfloat(v1, collum, pos) == getfloat(v2, collum, pos))
            ), "integer");
        }
    }
    else if(op == "大") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer" && v2.second == "integer") {
            return pair<Value*, string>(new Value((long)(v1.first->i > v2.first->i)), "integer");
        }
        else {
            return pair<Value*, string>(new Value(
                (long)(getfloat(v1, collum, pos) > getfloat(v2, collum, pos))
            ), "integer");
        }
    }
    else if(op == "小") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer" && v2.second == "integer") {
            return pair<Value*, string>(new Value((long)(v1.first->i < v2.first->i)), "integer");
        }
        else {
            return pair<Value*, string>(new Value(
                (long)(getfloat(v1, collum, pos) == getfloat(v2, collum, pos))
            ), "integer");
        }
    }
    else if(op == "違") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer" && v2.second == "integer") {
            return pair<Value*, string>(new Value((long)(v1.first->i != v2.first->i)), "integer");
        }
        else {
            return pair<Value*, string>(new Value(
                (long)(getfloat(v1, collum, pos) == getfloat(v2, collum, pos))
            ), "integer");
        }
    }
    else if(op == "且") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer" && v2.second == "integer") {
            return pair<Value*, string>(new Value((long)(v1.first->i && v2.first->i)), "integer");
        }
        throw runtime_error(invalid_type(collum, pos, "integer", "type"));
    }
    else if(op == "或") {
        pair<Value*, string> v1 = exp1->getValue();
        pair<Value*, string> v2 = exp2->getValue();
        if(v1.second == "integer" && v2.second == "integer") {
            return pair<Value*, string>(new Value((long)(v1.first->i || v2.first->i)), "integer");
        }
        throw runtime_error(invalid_type(collum, pos, "integer", "type"));
    }
    else if(op == "是") {
        // dynamic_cast を使い、キャスト成功を確認
        Variable* var = dynamic_cast<Variable*>(exp1);
        if (var) {
            string name = var->getname();
            pair<Value*, string> result = exp2->getValue();
            Environments::setvar(name, result);
            return result;
        }

        // Variable へのキャストが失敗した場合
        Index* index = dynamic_cast<Index*>(exp1);
        if (index) {
            pair<Value*, string> result = exp2->getValue();
            index->assign(result);
            return result;
        }

        // Variable へのキャストが失敗した場合
        ObjectIndex* objindex = dynamic_cast<ObjectIndex*>(exp1);
        if (objindex) {
            pair<Value*, string> result = exp2->getValue();
            objindex->assign(result);
            return result;
        }

        // 両方のキャストが失敗した場合
        throw runtime_error(invalid_type_assign(collum, pos));
    }
    throw runtime_error(invalid_type(collum, pos, "number", exp1->getValue().second));
}
