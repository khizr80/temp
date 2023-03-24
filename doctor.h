#include"User.h"

using namespace System::Data::SqlClient;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

public ref class doctor : public User
{
public:
	String^ specialization;
	bool login(String^ i, String^ pass)
	{

		String^ id = i;
		String^ password = pass;

		if (id->Length == 0 || password->Length == 0) {
			MessageBox::Show("Please enter email and password", "Email or Password Empty", MessageBoxButtons::OK);
			return 0;
		}

		try {
			String^ connString = "Data Source=DESKTOP-9T5F2B3;Initial Catalog=mono;Integrated Security=True;";
			SqlConnection sqlConn(connString);
			sqlConn.Open();
			String^ sqlQuery = "SELECT * FROM [doctor] WHERE id=@id AND password=@password";
			SqlCommand command(sqlQuery, % sqlConn);
			command.Parameters->AddWithValue("@id", id);
			command.Parameters->AddWithValue("@password", password);
			SqlDataReader^ reader = command.ExecuteReader();
			if (reader->Read()) {

				this->id = reader->GetString(0);
				 this->password = reader->GetString(1);
				 first_name = reader->GetString(2);
				 last_name = reader->GetString(3);
				 specialization = reader->GetString(4);
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
	void forget_passowrd(String^ i, String^ q)
	{
		try
		{
			id = i;
			security_q = q;
			String^ connString = "Data Source=DESKTOP-9T5F2B3;Initial Catalog=mono;Integrated Security=True";
			SqlConnection sqlConn(connString);
			sqlConn.Open();
			String^ sqlQuery = "SELECT password FROM [doctor] WHERE id=@id AND security_q=@security_q";
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
	int change_detail(String^ f, String^ l, String^ i, String^ p, String^ in, String^ se, String^ a, String^ ph)
	{
		id = i;
		password = p;
		first_name = f;
		last_name = l;
		specialization = in;
		security_q = se;
		phone_no = ph;
		age = a;
		if (first_name->Length == 0 || last_name->Length == 0 || phone_no->Length == 0 || id->Length == 0
			|| password->Length == 0 || specialization->Length == 0 || age->Length == 0)
		{
			return 2;
		}
		try {
			String^ connString = "Data Source=DESKTOP-9T5F2B3;Initial Catalog=mono;Integrated Security=True";
			SqlConnection sqlConn(connString);
			sqlConn.Open();
			String^ sqlQuery = "UPDATE [doctor] SET first_name = @first_name, last_name = @last_name, specialization = @specialization, age = @age, phone_no = @phone_no, password = @password, security_q = @security_q WHERE id = @id";
			SqlCommand command(sqlQuery, % sqlConn);
			command.Parameters->AddWithValue("@id", id);
			command.Parameters->AddWithValue("@first_name", first_name);
			command.Parameters->AddWithValue("@last_name", last_name);
			command.Parameters->AddWithValue("@specialization", specialization);
			command.Parameters->AddWithValue("@age", age);
			command.Parameters->AddWithValue("@phone_no", phone_no);
			command.Parameters->AddWithValue("@password", password);
			command.Parameters->AddWithValue("@security_q", security_q);
			command.ExecuteNonQuery();
			return 0;
		}
		catch (Exception^ ex)
		{
			return 1;
		}
	}
};
