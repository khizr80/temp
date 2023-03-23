#pragma once


using namespace System;

public ref class User {
public:
	String^ id;
	String^ password;
	String^ first_name;
	String^ last_name;
	String^ phone_no;
	String^ security_q;
	String^ confirm_password;
	String^ age;

};

public ref class Patient : public User
{
public:
	String^ insurance_no;
};
public ref class doctor : public User
{
public:
	String^ specialization;
};
public ref class admin : public User
{
public:
	String^ revenue;
};