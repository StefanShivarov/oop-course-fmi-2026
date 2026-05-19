#include "EventProfit.h"

EventProfit::EventProfit(
	double expenseForEvent,
	double expenseForUser,
	double sumForCharity,
	double profitTaxRate,

	bool useExpenseForEvent,
	bool useExpenseForUser,
	bool useSumForCharity,
	bool useProfitTaxRate)

	: expenseForEvent(expenseForEvent),
	 expenseForUser(expenseForUser),
	 sumForCharity(sumForCharity),
	 profitTaxRate(profitTaxRate),

	 useExpenseForEvent(useExpenseForEvent),
	 useExpenseForUser(useExpenseForUser),
	 useSumForCharity(useSumForCharity),
	 useProfitTaxRate(useProfitTaxRate)
{}

double EventProfit::operator()(double income, size_t participantsCount) const
{
	double expenses = 0.0;

	if (useExpenseForEvent) {
		expenses += expenseForEvent;
	}

	if (useExpenseForUser) {
		expenses += (expenseForUser * participantsCount);
	}

	if (useProfitTaxRate) {
		expenses += (profitTaxRate * income);
	}

	double expectedProfit = income - expenses;

	if (useSumForCharity) {
		expectedProfit -= sumForCharity;
	}

	return expectedProfit;
}


EventProfit::Builder EventProfit::builder()
{
	return Builder();
}

EventProfit::Builder& EventProfit::Builder::withExpenseForEvent(double m)
{
	expenseForEvent = m;
	useExpenseForEvent = true;
	return *this;
}

EventProfit::Builder& EventProfit::Builder::withExpenseForUser(double m)
{
	expenseForUser = m;
	useExpenseForUser= true;
	return *this;
}

EventProfit::Builder& EventProfit::Builder::withSumForCharity(double m)
{
	sumForCharity = m;
	useSumForCharity = true;
	return *this;
}

EventProfit::Builder& EventProfit::Builder::withProfitTaxRate(double m)
{
	profitTaxRate = m;
	useProfitTaxRate = true;
	return *this;
}

EventProfit EventProfit::Builder::build() const
{
	return EventProfit(
		 expenseForEvent,
		 expenseForUser,
		 sumForCharity,
		 profitTaxRate,

		 useExpenseForEvent,
		 useExpenseForUser,
		 useSumForCharity,
		 useProfitTaxRate);
}