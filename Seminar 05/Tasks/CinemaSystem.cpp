#include "CinemaSystem.h"

void CinemaSystem::recize()
{
	Screening* newArr = new Screening[screeningsCapacity + DEFAULT_RECIZE];
	for (unsigned i = 0; i < screeningsCount; i++) {
		newArr[i] = screenings[i];
	}
	delete[] screenings;
	screenings = newArr;
	screeningsCapacity += DEFAULT_RECIZE;
}

Screening* CinemaSystem::findScreeningById(unsigned screeningId)
{
	for (unsigned i = 0; i < screeningsCount; i++) {
		if (screenings[i].getId() == screeningId) {
			return &screenings[i];
		}
	}
	return nullptr;
}

const Screening* CinemaSystem::findScreeningById(unsigned screeningId) const
{
	for (unsigned i = 0; i < screeningsCount; i++) {
		if (screenings[i].getId() == screeningId) {
			return &screenings[i];
		}
	}
	return nullptr;
}

void CinemaSystem::copyDynamicMemory(const CinemaSystem& other)
{
	screenings = new Screening[other.screeningsCapacity];

	for (unsigned i = 0; i < other.screeningsCount; i++) {
		screenings[i] = other.screenings[i];
	}
}

void CinemaSystem::free()
{
	delete[] screenings;
	screenings = nullptr;
	screeningsCount = 0;
}

void CinemaSystem::copyFrom(const CinemaSystem& other)
{
	screeningsCapacity = other.screeningsCapacity;
	screeningsCount = other.screeningsCount;
	copyDynamicMemory(other);
}

CinemaSystem::CinemaSystem() : screeningsCount(0), screeningsCapacity(DEFAULT_RECIZE)
{
	screenings = new Screening[screeningsCapacity];
}

CinemaSystem::CinemaSystem(const CinemaSystem& other)
{
	copyFrom(other);
}

CinemaSystem& CinemaSystem::operator=(const CinemaSystem& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

CinemaSystem::~CinemaSystem()
{
	free();
}

bool CinemaSystem::addScreening(const Screening& screening)
{
	if (!screening.getMovie() || !screening.getHall()) {
		return false;
	}

	if (screeningsCount >= screeningsCapacity) recize();

	screenings[screeningsCount++] = screening;
	return true;
}

bool CinemaSystem::addScreening(const Movie* movie, const Hall* hall, const Date& date, const Time& time)
{
	return addScreening(Screening(movie, hall, date, time));
}

bool CinemaSystem::removeScreening(unsigned screeningId)
{
	for (unsigned i = 0; i < screeningsCount; i++) {
		if (screenings[i].getId() == screeningId) {
			for (unsigned j = i; j < screeningsCount - 1; j++) {
				screenings[j] = screenings[j + 1];
			}
			screeningsCount--;
			return true;
		}
	}
	return false;
}

bool CinemaSystem::reserveSeat(unsigned screeningId, unsigned seatNumber)
{
	Screening* screening = findScreeningById(screeningId);
	if (!screening) return false;

	return screening->reserveSeat(seatNumber);
}

bool CinemaSystem::releaseSeat(unsigned screeningId, unsigned seatNumber)
{
	Screening* screening = findScreeningById(screeningId);
	if (!screening) return false;

	return screening->releaseSeat(seatNumber);
}

bool CinemaSystem::isSeatFree(unsigned screeningId, unsigned seatNumber) const
{
	const Screening* screening = findScreeningById(screeningId);
	if (!screening) return false;

	return screening-> isSeatFree(seatNumber);
}

unsigned CinemaSystem::getFreeSeatsCount(unsigned screeningId) const
{
	for (unsigned i = 0; i < screeningsCount; i++) {
		if (screenings[i].getId() == screeningId) {
			return screenings[i].getFreeSeatsCount();
		}
	}
	return 0;
}

const Screening* CinemaSystem::getScreeningById(unsigned screeningId) const
{
	return findScreeningById(screeningId);
}

unsigned CinemaSystem::getScreeningsCount() const
{
	return screeningsCount;
}

const Screening* CinemaSystem::getScreeningAt(unsigned index) const
{
	if (index >= screeningsCount) {
		return nullptr;
	}

	return &screenings[index];
}

void printAllScreenings(const CinemaSystem& c, std::ostream& os)
{
	if (c.getScreeningsCount() == 0) {
		os << "No screenings available.\n";
		return;
	}

	for (unsigned i = 0; i < c.getScreeningsCount(); i++) {
		const Screening* s = c.getScreeningAt(i);
		if (s != nullptr) {
			printScreening(*s, os);
		}
	}
}
