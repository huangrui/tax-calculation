#include<iostream>
#include<vector>

using namespace std;

double Month_salary(const int, const double);
double Total_salary(const vector<int>&, const double&);
void Backtrack(int, int, const int&, const vector<int>&, vector<int>&, vector<int>&, const double&, double&);

int main()
{
	double day_salary = 0; 
	cout<<"Please input your salary per day:"<<endl;
	cin>>day_salary;
	vector<int> months;
	int value, k=0;
	cout<<"Please input your work days of months(input -1 to end):"<<endl;
	while(cin >> value && value != -1)
		months.push_back(value);

	vector<int> max_months(months),x(months);
	double max_payment = 0;
	int total_days = 0;
	for(vector<int>::iterator iter = months.begin(); iter != months.end(); ++iter)
		total_days += *iter;
	
	cout<<endl;
	// Backtrack
	Backtrack(0, k, total_days, months, x, max_months, day_salary, max_payment);	


	cout<<"\nAbove all, if you submit work days normally like:";
	for(vector<int>::iterator iter = months.begin(); iter != months.end(); ++iter)
		cout<<*iter<<"("<<Month_salary(*iter, day_salary)<<") ";
	cout<<endl;
	cout<<"The normal salary is "<<Total_salary(months, day_salary)<<"\n";
	cout<<"The normal salary per month is "<<Total_salary(months, day_salary) / months.size()<<"\n";
	
	cout<<"So you should submit work days like:";
	for(vector<int>::iterator iter = max_months.begin(); iter != max_months.end(); ++iter)
		cout<<*iter<<"("<<Month_salary(*iter, day_salary)<<") ";
	cout<<endl;
	
	cout<<"The maximum salary is "<<max_payment<<"\n";
	cout<<"The maximum salary per month is "<<max_payment / max_months.size()<<"\n";
	cout<<"You would save about "<<max_payment-Total_salary(months, day_salary)<<" entirely."<<endl;
	
	cout<<"The lower tax is "<<(max_payment - Total_salary(months, day_salary)) / months.size()<<" per month."<<endl;
	return 0;
}

// x is vector<int> mid value
void Backtrack(int t, int k, const int &total_days, const vector<int> &months, vector<int> &x, vector<int> &max_months, const double &day_salary, double &max_payment)
{
	if (t > months.size()-1 || months.size() == 1)
	{
		double total = Total_salary(x,day_salary);
		cout<<"The total salary is "<<total<<", when you submit work days like:\n";
		for(vector<int>::iterator iter = x.begin(); iter != x.end(); ++iter)
			cout<<*iter<<" ";
		cout<<"\n";
		if (total > max_payment)
		{
			for(vector<int>::size_type i = 0; i != x.size(); ++i)
				max_months[i] = x[i];
			max_payment = total;
		}
	}
	else
	{
		int top = months[0], bottom = 0;
		for(int j = 1; j <= t; ++j)
			top += months[j] - x[j-1];

		if (t > 0)
			bottom = x[t-1];
		for(int i = bottom; i <= top; ++i)
		{
			x[t] = i;
			k += x[t];
			if (t == months.size()-2)
			{
				x[t+1] = total_days - k;
				if (x[t+1] >= x[t])
					Backtrack(t+2,k,total_days,months,x,max_months,day_salary,max_payment);
			}	
			else
				Backtrack(t+1,k,total_days,months,x,max_months,day_salary,max_payment);
			k -= x[t];
		}
	}
}

double Month_salary(const int days, const double day_salary)
{
/*	if ( days < 0 || day_salary < 0)
	{
		cout<<"The work days and salary per day is error!!!"<<endl;
		return -1;
	}
	if (days > 31)
	{
		cout<<"The work days should be below 31!!!"<<endl;
		return -1;
	}
*/

	if ((double)days*day_salary < 800)
		return (double)days*day_salary;
	else
		if ((double)days*day_salary < 4000)	
			return (double)days*day_salary - ((double)days*day_salary-800)*0.2;
		else
			return (double)days*day_salary*(1-0.8*0.2);
}

double Total_salary(const vector<int> &months, const double &day_salary)
{
	double payment = 0;
	for(vector<int>::const_iterator iter = months.begin(); iter != months.end(); ++iter)
		payment+=Month_salary(*iter, day_salary);
	return payment;
}
