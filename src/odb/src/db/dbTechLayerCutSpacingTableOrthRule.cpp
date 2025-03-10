///////////////////////////////////////////////////////////////////////////////
// BSD 3-Clause License
//
// Copyright (c) 2020, The Regents of the University of California
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

// Generator Code Begin Cpp
#include "dbTechLayerCutSpacingTableOrthRule.h"

#include "dbDatabase.h"
#include "dbTable.h"
#include "dbTable.hpp"
#include "dbTechLayerCutSpacingRule.h"
#include "odb/db.h"
// User Code Begin Includes
#include "dbTechLayer.h"
// User Code End Includes
namespace odb {
template class dbTable<_dbTechLayerCutSpacingTableOrthRule>;

bool _dbTechLayerCutSpacingTableOrthRule::operator==(
    const _dbTechLayerCutSpacingTableOrthRule& rhs) const
{
  return true;
}

bool _dbTechLayerCutSpacingTableOrthRule::operator<(
    const _dbTechLayerCutSpacingTableOrthRule& rhs) const
{
  return true;
}

_dbTechLayerCutSpacingTableOrthRule::_dbTechLayerCutSpacingTableOrthRule(
    _dbDatabase* db)
{
}

dbIStream& operator>>(dbIStream& stream,
                      _dbTechLayerCutSpacingTableOrthRule& obj)
{
  stream >> obj.spacing_tbl_;
  return stream;
}

dbOStream& operator<<(dbOStream& stream,
                      const _dbTechLayerCutSpacingTableOrthRule& obj)
{
  stream << obj.spacing_tbl_;
  return stream;
}

void _dbTechLayerCutSpacingTableOrthRule::collectMemInfo(MemInfo& info)
{
  info.cnt++;
  info.size += sizeof(*this);

  // User Code Begin collectMemInfo
  info.children_["spacing_tbl"].add(spacing_tbl_);
  // User Code End collectMemInfo
}

////////////////////////////////////////////////////////////////////
//
// dbTechLayerCutSpacingTableOrthRule - Methods
//
////////////////////////////////////////////////////////////////////

void dbTechLayerCutSpacingTableOrthRule::getSpacingTable(
    std::vector<std::pair<int, int>>& tbl) const
{
  _dbTechLayerCutSpacingTableOrthRule* obj
      = (_dbTechLayerCutSpacingTableOrthRule*) this;
  tbl = obj->spacing_tbl_;
}

// User Code Begin dbTechLayerCutSpacingTableOrthRulePublicMethods
void dbTechLayerCutSpacingTableOrthRule::setSpacingTable(
    std::vector<std::pair<int, int>> tbl)
{
  _dbTechLayerCutSpacingTableOrthRule* obj
      = (_dbTechLayerCutSpacingTableOrthRule*) this;
  obj->spacing_tbl_ = tbl;
}

dbTechLayerCutSpacingTableOrthRule* dbTechLayerCutSpacingTableOrthRule::create(
    dbTechLayer* parent)
{
  _dbTechLayer* _parent = (_dbTechLayer*) parent;
  _dbTechLayerCutSpacingTableOrthRule* newrule
      = _parent->cut_spacing_table_orth_tbl_->create();
  return ((dbTechLayerCutSpacingTableOrthRule*) newrule);
}

dbTechLayerCutSpacingTableOrthRule*
dbTechLayerCutSpacingTableOrthRule::getTechLayerCutSpacingTableOrthSubRule(
    dbTechLayer* parent,
    uint dbid)
{
  _dbTechLayer* _parent = (_dbTechLayer*) parent;
  return (dbTechLayerCutSpacingTableOrthRule*)
      _parent->cut_spacing_table_orth_tbl_->getPtr(dbid);
}
void dbTechLayerCutSpacingTableOrthRule::destroy(
    dbTechLayerCutSpacingTableOrthRule* rule)
{
  _dbTechLayer* _parent = (_dbTechLayer*) rule->getImpl()->getOwner();
  dbProperty::destroyProperties(rule);
  _parent->cut_spacing_table_orth_tbl_->destroy(
      (_dbTechLayerCutSpacingTableOrthRule*) rule);
}

// User Code End dbTechLayerCutSpacingTableOrthRulePublicMethods
}  // namespace odb
// Generator Code End Cpp
