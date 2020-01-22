/*
Copyright 2016 University of Auckland

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "libcellml/component.h"
#include "libcellml/logger.h"
#include "libcellml/types.h"

#include <algorithm>
#include <vector>

namespace libcellml {

/**
 * @brief The Logger::LoggerImpl struct.
 *
 * This struct is the private implementation struct for the LoggerImpl class.  Separating
 * the implementation from the definition allows for greater flexibility when
 * distributing the code.
 */
struct Logger::LoggerImpl
{
    std::vector<size_t> mErrors;
    std::vector<size_t> mWarnings;
    std::vector<size_t> mHints;
    std::vector<IssuePtr> mIssues;
};

Logger::Logger()
    : mPimpl(new LoggerImpl())
{
}

Logger::~Logger()
{
    delete mPimpl;
}

size_t Logger::errorCount() const
{
    return mPimpl->mErrors.size();
}

IssuePtr Logger::error(size_t index) const
{
    IssuePtr err = nullptr;
    if ((index < mPimpl->mErrors.size()) && (mPimpl->mErrors.at(index) < mPimpl->mIssues.size())) {
        err = mPimpl->mIssues.at(mPimpl->mErrors.at(index));
    }
    return err;
}

size_t Logger::warningCount() const
{
    return mPimpl->mWarnings.size();
}

IssuePtr Logger::warning(size_t index) const
{
    IssuePtr err = nullptr;
    if ((index < mPimpl->mWarnings.size()) && (mPimpl->mWarnings.at(index) < mPimpl->mIssues.size())) {
        err = mPimpl->mIssues.at(mPimpl->mWarnings.at(index));
    }
    return err;
}

size_t Logger::hintCount() const
{
    return mPimpl->mHints.size();
}

IssuePtr Logger::hint(size_t index) const
{
    IssuePtr err = nullptr;
    if ((index < mPimpl->mHints.size()) && (mPimpl->mHints.at(index) < mPimpl->mIssues.size())) {
        err = mPimpl->mIssues.at(mPimpl->mHints.at(index));
    }
    return err;
}

void Logger::removeAllIssues()
{
    mPimpl->mIssues.clear();
    mPimpl->mErrors.clear();
    mPimpl->mWarnings.clear();
    mPimpl->mHints.clear();
}

void Logger::addIssue(const IssuePtr &issue)
{
    // When an issue is added
    mPimpl->mIssues.push_back(issue);
    size_t index = mPimpl->mIssues.size() - 1;
    // Update the appropriate array based on its level

    libcellml::Issue::Level level = issue->level();
    // if (issue->isLevel(libcellml::Issue::Level::ERROR)) {
    //     mPimpl->mErrors.push_back(index);
    // }

    // if (issue->isLevel(libcellml::Issue::Level::WARNING)) {
    //     mPimpl->mWarnings.push_back(index);
    // }

    // if (issue->isLevel(libcellml::Issue::Level::HINT)) {
    //     mPimpl->mHints.push_back(index);
    // }
    // auto level = issue->level();

    // if (level == libcellml::Issue::Level::ERROR){
    //     mPimpl->mErrors.push_back(index);
    // }
    // else if (level == libcellml::Issue::Level::WARNING){
    //     mPimpl->mWarnings.push_back(index);
    // }
    // else if (level == libcellml::Issue::Level::HINT){
    //     mPimpl->mHints.push_back(index);
    // }

    switch (level) {
    case libcellml::Issue::Level::ERROR:
        mPimpl->mErrors.push_back(index);
        break;
    case libcellml::Issue::Level::WARNING:
        mPimpl->mWarnings.push_back(index);
        break;
    case libcellml::Issue::Level::HINT:
        mPimpl->mHints.push_back(index);
        break;
    }
}

size_t Logger::issueCount() const
{
    return mPimpl->mIssues.size();
}

IssuePtr Logger::issue(size_t index) const
{
    IssuePtr err = nullptr;
    if (index < mPimpl->mIssues.size()) {
        err = mPimpl->mIssues.at(index);
    }
    return err;
}

IssuePtr Logger::issue(size_t index, libcellml::Issue::Level level) const
{
    IssuePtr e = nullptr;
    switch (level) {
    case libcellml::Issue::Level::ERROR:
        e = error(index);
        break;
    case libcellml::Issue::Level::WARNING:
        e = warning(index);
        break;
    case libcellml::Issue::Level::HINT:
        e = hint(index);
        break;
    }
    return e;
}

IssuePtr Logger::issue(size_t index, std::vector<libcellml::Issue::Level> &levels) const
{
    size_t i = 0;
    index++;
    while (i < mPimpl->mIssues.size()) {
        for (auto issue : mPimpl->mIssues) {
            if (std::find(levels.begin(), levels.end(), issue->level()) != levels.end()) {
                i++;
            }
            if (i == index) {
                return issue;
            }
        }
    }
    return nullptr;
}

} // namespace libcellml
