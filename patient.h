#pragma once
#include<iostream>
#include"User.h"
using namespace std;
public ref class Patient : public User
{
public:
	String^ insurance_no;
};