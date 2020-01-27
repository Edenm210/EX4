//
// Created by eden on 16/01/2020.
//

#ifndef EX4__ISEARCHER_H_
#define EX4__ISEARCHER_H_

#include "SearchableGraph.h"

template <class P, class S>
class ISearcher {
 public:
  virtual S search(ISearchable<P> *searchable)=0;

  virtual int getNumberOfNodesEvaluated()=0;

 // virtual ISearcher* copySearcher();

  virtual string getSearcherName()=0;

  virtual ISearcher* copySearcher()=0;


  };

#endif //EX4__ISEARCHER_H_
