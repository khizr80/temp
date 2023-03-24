#include"User.h"

using namespace System::Data::SqlClient;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

public ref class Patient : public User
{
public:
	String^ insurance_no;
	bool login(String^ i, String^ pass)
	{
		
		String^ id = i;
		String^ password = pass;

		if (id->Length == 0 || password->Length == 0) {
			MessageBox::Show("Please enter email and password","Email or Password Empty", MessageBoxButtons::OK);
			return 0;
		}

		try {
			String^ connString = "Data Source=DESKTOP-9T5F2B3;Initial Catalog=mono;Integrated Security=True;";
			SqlConnection sqlConn(connString);
			sqlConn.Open();
			String^ sqlQuery = "SELECT * FROM [user] WHERE id=@no AND password=@pwd";
			SqlCommand command(sqlQuery, % sqlConn);
			command.Parameters->AddWithValue("@no", id);
			command.Parameters->AddWithValue("@pwd", password);
			SqlDataReader^ reader = command.ExecuteReader();
			if (reader->Read()) {
				
				id = reader->GetString(0);
				 password = reader->GetString(1);
				 first_name = reader->GetString(2);
				 last_name = reader->GetString(3);
				 insurance_no = reader->GetString(4);
				 security_q = reader->GetString(5);
				 age = reader->GetString(6);
				 phone_no = reader->GetString(7);
				 return 1;
				//MessageBox::Show("" + user->first_name + user->last_name + user->id + user->password + user->insurance_no
					//+ user->security_q + user->age + user->phone_no + user->role, "message", MessageBoxButtons::OK);
			}
			else {
				MessageBox::Show("Email or password is incorrect",
					"Email or Password Error", MessageBoxButtons::OK);
				return 0;
			}
		}
		catch (Exception^ e) {
			MessageBox::Show("Failed to connect to database", "Database Connection Error", MessageBoxButtons::OK);
			return 0;
		}
	
	}
	void signup(String^i, String^ p, String^ f, String^ l, String^ in, String^ se, String^ a, String^ ph, String^ con)
	{
		id = i;
		password = p;
		first_name = f;
		last_name = l;
		insurance_no = in;
		security_q = se;
		age = a;
		phone_no = ph;
		confirm_password = con;
		if (first_name->Length == 0 || last_name->Length == 0 || phone_no->Length == 0 || id->Length == 0
			|| password->Length == 0 || insurance_no->Length == 0 || age->Length == 0 || confirm_password->Length == 0)
		{

			MessageBox::Show("Please enter all the fields", "On or more empty fields", MessageBoxButtons::OK);
			return;
		}
		if (String::Compare(password, confirm_password) != 0) {
			MessageBox::Show("Password and Confirm Password do not match", "Password Error", MessageBoxButtons::OK);
			return;
		}
		try {
			String^ connString = "Data Source=DESKTOP-9T5F2B3;Initial Catalog=mono;Integrated Security=True";
			SqlConnection sqlConn(connString);
			sqlConn.Open();
			String^ sqlQuery = "INSERT INTO [user] (first_name, last_name, id, insurance_no, age, phone_no, password,security_q) VALUES (@first_name, @last_name, @id, @insurance_no, @age, @phone_no, @password,@security_q)";
			SqlCommand command(sqlQuery, % sqlConn);
			command.Parameters->AddWithValue("@id", id);
			command.Parameters->AddWithValue("@first_name", first_name);
			command.Parameters->AddWithValue("@last_name", last_name);
			command.Parameters->AddWithValue("@insurance_no", insurance_no);
			command.Parameters->AddWithValue("@age", age);
			command.Parameters->AddWithValue("@phone_no", phone_no);
			command.Parameters->AddWithValue("@password", password);
			command.Parameters->AddWithValue("@security_q", security_q);
			command.ExecuteNonQuery();
			
		}
		catch (Exception^ ex)
		{
			MessageBox::Show("Failed to register new user", "Register Failure", MessageBoxButtons::OK);
		}

	}
	void forget_passowrd(String^ i, String^ q)
	{
		try
		{
			id = i;
			security_q = q;
			String^ connString = "Data Source=DESKTOP-9T5F2B3;Initial Catalog=mono;Integrated Security=True";
			SqlConnection sqlConn(connString);
			sqlConn.Open();
			String^ sqlQuery = "SELECT password FROM [user] WHERE id=@id AND security_q=@security_q";
			SqlCommand command(sqlQuery, % sqlConn);
			command.Parameters->AddWithValue("@id", id);
			command.Parameters->AddWithValue("@security_q", security_q);
			SqlDataReader^ reader = command.ExecuteReader();
			String^ password;
			if (reader->Read()) {
				password = reader->GetString(0);
			}
			MessageBox::Show("your password is \n" + password, "your password ", MessageBoxButtons::OK);
		}
		catch (Exception^ ex)
		{
			MessageBox::Show("Id or security question incorrect", "Forget password Failure", MessageBoxButtons::OK);
		}
	}
};