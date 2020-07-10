// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/Unit.h
//! @brief     Defines class Unit.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARAMETRIZATION_UNIT_H
#define BORNAGAIN_CORE_PARAMETRIZATION_UNIT_H

#include <darefl/minikernel/Basics/INamed.h>
#include <string>

//! A physical unit.

class Unit : public INamed
{
public:
    explicit Unit(const std::string& name = "") { setUnit(name); }
    void setUnit(const std::string& name);
};

#endif // BORNAGAIN_CORE_PARAMETRIZATION_UNIT_H
