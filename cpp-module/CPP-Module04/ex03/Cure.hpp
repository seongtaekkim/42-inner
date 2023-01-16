#ifndef CURE_HPP
# define CURE_HPP

#include <string>
#include "AMateria.hpp"

#define C_NAME "cure"

class Cure : public AMateria {
public:
	Cure(void);
	Cure(const Cure& i);
	Cure(const std::string& type);
	virtual ~Cure(void);
	Cure& operator=(const Cure& c);
	AMateria* clone(void) const;
	virtual void use(const ICharacter& ic);
};

#endif