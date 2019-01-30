/*
 * Copyright ©2018 Justin Hsia.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Spring Quarter 2018 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <iostream>
#include <algorithm>

#include "./QueryProcessor.h"

extern "C" {
  #include "./libhw1/CSE333.h"
}

namespace hw3 {

// helper function to find all the common element containing same docid
// and return a list of them with the sum of their occurances
static list<docid_element_header> MergeResults
       (const list<docid_element_header>&, const list<docid_element_header>&);

QueryProcessor::QueryProcessor(list<string> indexlist, bool validate) {
  // Stash away a copy of the index list.
  indexlist_ = indexlist;
  arraylen_ = indexlist_.size();
  Verify333(arraylen_ > 0);

  // Create the arrays of DocTableReader*'s. and IndexTableReader*'s.
  dtr_array_ = new DocTableReader *[arraylen_];
  itr_array_ = new IndexTableReader *[arraylen_];

  // Populate the arrays with heap-allocated DocTableReader and
  // IndexTableReader object instances.
  list<string>::iterator idx_iterator = indexlist_.begin();
  for (HWSize_t i = 0; i < arraylen_; i++) {
    FileIndexReader fir(*idx_iterator, validate);
    dtr_array_[i] = new DocTableReader(fir.GetDocTableReader());
    itr_array_[i] = new IndexTableReader(fir.GetIndexTableReader());
    idx_iterator++;
  }
}

QueryProcessor::~QueryProcessor() {
  // Delete the heap-allocated DocTableReader and IndexTableReader
  // object instances.
  Verify333(dtr_array_ != nullptr);
  Verify333(itr_array_ != nullptr);
  for (HWSize_t i = 0; i < arraylen_; i++) {
    delete dtr_array_[i];
    delete itr_array_[i];
  }

  // Delete the arrays of DocTableReader*'s and IndexTableReader*'s.
  delete[] dtr_array_;
  delete[] itr_array_;
  dtr_array_ = nullptr;
  itr_array_ = nullptr;
}

vector<QueryProcessor::QueryResult>
QueryProcessor::ProcessQuery(const vector<string> &query) {
  Verify333(query.size() > 0);
  vector<QueryProcessor::QueryResult> finalresult;

  // MISSING:
  // iterate through each index file
  for (HWSize_t i = 0; i < arraylen_; i++) {
    DocTableReader* dtr_ptr = dtr_array_[i];
    IndexTableReader* itr_ptr = itr_array_[i];

    // look up for the first word in the query
    // search for next index file if word is not found
    DocIDTableReader* didtr_0 = itr_ptr->LookupWord(query[0]);
    if (didtr_0 == NULL) {
      delete(didtr_0);  // free object
      continue;
    }

    // get the docidlist for query[0]
    list<docid_element_header> result = didtr_0->GetDocIDList();

    // iterate through each word
    for (HWSize_t j = 1; j < query.size(); j++) {
      // look up for the first word in the query
      // search for next index file if word is not found
      DocIDTableReader* didtr_tmp = itr_ptr->LookupWord(query[j]);
      if (didtr_tmp == NULL) {
        result.clear();
        delete(didtr_tmp);  // free object
        break;
      }

      // get the docidlist for query[j]
      list<docid_element_header> result_tmp = didtr_tmp->GetDocIDList();
      result = MergeResults(result, result_tmp);

      delete(didtr_tmp);  // free object
    }

    // no file contains all words in the query in this
    // index file, skip to next one
    if (result.size() == 0) {
      delete(didtr_0);  // free object
      continue;
    } else {
      for (auto const& el : result) {
        DocID_t  docid = el.docid;
        HWSize_t  num_positions = el.num_positions;
        QueryProcessor::QueryResult qres;

        // find the filename corresponding to docid
        Verify333(dtr_ptr->LookupDocID(docid, &qres.document_name));
        qres.rank = num_positions;

        // insert to the end of finalresult
        finalresult.push_back(qres);
      }
    }

    delete(didtr_0);  // free object
  }

  // Sort the final results.
  std::sort(finalresult.begin(), finalresult.end());
  return finalresult;
}

static list<docid_element_header> MergeResults
       (const list<docid_element_header> &list1,
       const list<docid_element_header> &list2) {
  list<docid_element_header>::iterator it1;
  list<docid_element_header>::iterator it2;
  list<docid_element_header> list_final;

  // iterate through the first list
  for (auto const& i : list1) {
    DocID_t docid = i.docid;
    HWSize_t num_positions = i.num_positions;
    bool found = false;

    // iterate through the second list
    for (auto const& j : list2) {
      if (j.docid == docid) {  // found matched docid
        found = true;
        num_positions += j.num_positions;  // update rank
        break;
      }
    }

    if (found)
      // insert to the end of list_final
      list_final.push_back(docid_element_header{docid, num_positions});
  }

  return list_final;
}

}  // namespace hw3
