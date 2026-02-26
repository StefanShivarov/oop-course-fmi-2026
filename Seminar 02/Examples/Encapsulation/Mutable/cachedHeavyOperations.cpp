class ExpensiveCalculationCache {
    int x;
    mutable bool cached = false;
    mutable int cachedValue = 0;

public:
    int calculate() const {
        if (!cached) {
            //... some expensive calculation based on x
            cachedValue = x * x; // imagine the calculation
                                // requires a lot of operations and resources
                                // and we might call it multiple times, so we want to cache the result
            cached = true;
        }
        return cachedValue;
    }
};