#pragma once
class EventProfit
{
public:
	class Builder;

private:
	double expenseForEvent;
	double expenseForUser;
	double sumForCharity;
	double profitTaxRate;

	bool useExpenseForEvent;
	bool useExpenseForUser;
	bool useSumForCharity;
	bool useProfitTaxRate;

	EventProfit(
		double expenseForEvent,
		double expenseForUser,
		double sumForCharity,
		double profitTaxRate,

		bool useExpenseForEvent,
		bool useExpenseForUser,
		bool useSumForCharity,
		bool useProfitTaxRate
	);

public:
	double operator()(double income, size_t participantsCount) const;

	static Builder builder();
};

class EventProfit::Builder {
private:
	double expenseForEvent = 0;
	double expenseForUser = 0;
	double sumForCharity = 0;
	double profitTaxRate = 0;

	bool useExpenseForEvent = false;
	bool useExpenseForUser = false;
	bool useSumForCharity = false;
	bool useProfitTaxRate = false;

public:
	Builder() = default;
	//Builder(const Builder& other) = delete;
	//Builder& operator=(const Builder& other) = delete;

	Builder& withExpenseForEvent(double m);
	Builder& withExpenseForUser(double m);
	Builder& withSumForCharity(double m);
	Builder& withProfitTaxRate(double m);

	EventProfit build() const;
};
