/*
 * Tencent is pleased to support the open source community by making
 * WCDB available.
 *
 * Copyright (C) 2017 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *       https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __WCDB_ERROR_HPP
#define __WCDB_ERROR_HPP

#include <WCDB/String.hpp>
#include <functional>
#include <map>
#include <sstream>

namespace WCDB {

class Error final {
#pragma mark - Level
public:
    enum class Level : int {
        Ignore = 1,
        Debug = 2,
        Warning = 3,
        Notice = 4,
        Error = 5,
        Fatal = 6,
    };
    Level level;
    static constexpr const char *levelName(const Level &level)
    {
        switch (level) {
        case Level::Ignore:
            return "IGNORE";
        case Level::Debug:
            return "DEBUG";
        case Level::Warning:
            return "WARNING";
        case Level::Notice:
            return "NOTICE";
        case Level::Error:
            return "ERROR";
        case Level::Fatal:
            return "FATAL";
        }
    }

#pragma mark - Code
public:
    enum class Code : int {
        OK = 0,
        Error = 1,
        Internal = 2,
        Permission = 3,
        Abort = 4,
        Busy = 5,
        Locked = 6,
        NoMemory = 7,
        Readonly = 8,
        Interrupt = 9,
        IOError = 10,
        Corrupt = 11,
        NotFound = 12,
        Full = 13,
        CantOpen = 14,
        Protocol = 15,
        Empty = 16,
        Schema = 17,
        Exceed = 18,
        Constraint = 19,
        Mismatch = 20,
        Misuse = 21,
        NoLargeFileSupport = 22,
        Authorization = 23,
        Format = 24,
        Range = 25,
        NotADatabase = 26,
        Notice = 27,
        Warning = 28,
        Row = 100,
        Done = 101,
    };
    static Error::Code rc2c(int rc);
    static int c2rc(Error::Code code);
    static bool isError(int rc);
    static constexpr const char *codeName(const Code &code)
    {
        switch (code) {
        case Code::OK:
            return "OK";
        case Code::Error:
            return "Error";
        case Code::Internal:
            return "Internal";
        case Code::Permission:
            return "Permission";
        case Code::Abort:
            return "Abort";
        case Code::Busy:
            return "Busy";
        case Code::Locked:
            return "Locked";
        case Code::NoMemory:
            return "NoMemory";
        case Code::Readonly:
            return "Readonly";
        case Code::Interrupt:
            return "Interrupt";
        case Code::IOError:
            return "IOError";
        case Code::Corrupt:
            return "Corrupt";
        case Code::NotFound:
            return "NotFound";
        case Code::Full:
            return "Full";
        case Code::CantOpen:
            return "CantOpen";
        case Code::Protocol:
            return "Protocol";
        case Code::Empty:
            return "Empty";
        case Code::Schema:
            return "Schema";
        case Code::Exceed:
            return "Exceed";
        case Code::Constraint:
            return "Constraint";
        case Code::Mismatch:
            return "Mismatch";
        case Code::Misuse:
            return "Misuse";
        case Code::NoLargeFileSupport:
            return "NoLargeFileSupport";
        case Code::Authorization:
            return "Authorization";
        case Code::Format:
            return "Format";
        case Code::Range:
            return "Range";
        case Code::NotADatabase:
            return "NotADatabase";
        case Code::Notice:
            return "Notice";
        case Code::Warning:
            return "Warning";
        case Code::Row:
            return "Row";
        case Code::Done:
            return "Done";
        }
    }

    Code code() const;
    bool isOK() const;
    bool isCorruption() const;

    void setSystemCode(int systemCode, Code codeIfUnresolved);
    void setSQLiteCode(int code, int extendedCode);
    void setCode(Code code);
    void setCode(Code code, const String &source);

protected:
    Code m_code;

#pragma mark - ExtCode
public:
    enum class ExtCode : int {
        ErrorMissingCollseq = ((int) Code::Error | (1 << 8)),
        ErrorRetry = ((int) Code::Error | (2 << 8)),
        ErrorSnapshot = ((int) Code::Error | (3 << 8)),
        IOErrorRead = ((int) Code::IOError | (1 << 8)),
        IOErrorShortRead = ((int) Code::IOError | (2 << 8)),
        IOErrorWrite = ((int) Code::IOError | (3 << 8)),
        IOErrorFsync = ((int) Code::IOError | (4 << 8)),
        IOErrorDirFsync = ((int) Code::IOError | (5 << 8)),
        IOErrorTruncate = ((int) Code::IOError | (6 << 8)),
        IOErrorFstat = ((int) Code::IOError | (7 << 8)),
        IOErrorUnlock = ((int) Code::IOError | (8 << 8)),
        IOErrorRdlock = ((int) Code::IOError | (9 << 8)),
        IOErrorDelete = ((int) Code::IOError | (10 << 8)),
        IOErrorBlocked = ((int) Code::IOError | (11 << 8)),
        IOErrorNoMemory = ((int) Code::IOError | (12 << 8)),
        IOErrorAccess = ((int) Code::IOError | (13 << 8)),
        IOErrorCheckReservedLock = ((int) Code::IOError | (14 << 8)),
        IOErrorLock = ((int) Code::IOError | (15 << 8)),
        IOErrorClose = ((int) Code::IOError | (16 << 8)),
        IOErrorDirClose = ((int) Code::IOError | (17 << 8)),
        IOErrorShmOpen = ((int) Code::IOError | (18 << 8)),
        IOErrorShmSize = ((int) Code::IOError | (19 << 8)),
        IOErrorShmLock = ((int) Code::IOError | (20 << 8)),
        IOErrorShmMap = ((int) Code::IOError | (21 << 8)),
        IOErrorSeek = ((int) Code::IOError | (22 << 8)),
        IOErrorDeleteNoEntry = ((int) Code::IOError | (23 << 8)),
        IOErrorMmap = ((int) Code::IOError | (24 << 8)),
        IOErrorGetTempPath = ((int) Code::IOError | (25 << 8)),
        IOErrorConvPath = ((int) Code::IOError | (26 << 8)),
        IOErrorVnode = ((int) Code::IOError | (27 << 8)),
        IOErrorAuthorization = ((int) Code::IOError | (28 << 8)),
        IOErrorBeginAtomic = ((int) Code::IOError | (29 << 8)),
        IOErrorCommitAtomic = ((int) Code::IOError | (30 << 8)),
        IOErrorRollbackAtomic = ((int) Code::IOError | (31 << 8)),
        LockedSharedCache = ((int) Code::Locked | (1 << 8)),
        LockedVirtualTable = ((int) Code::Locked | (2 << 8)),
        BusyRecovery = ((int) Code::Busy | (1 << 8)),
        BusySnapshot = ((int) Code::Busy | (2 << 8)),
        CantOpenNoTempDir = ((int) Code::CantOpen | (1 << 8)),
        CantOpenIsDir = ((int) Code::CantOpen | (2 << 8)),
        CantOpenFullPath = ((int) Code::CantOpen | (3 << 8)),
        CantOpenConvPath = ((int) Code::CantOpen | (4 << 8)),
        CantOpenDirtyWal = ((int) Code::CantOpen | (5 << 8)),
        CorruptVirtualTable = ((int) Code::Corrupt | (1 << 8)),
        CorruptSequence = ((int) Code::Corrupt | (2 << 8)),
        ReadonlyRecovery = ((int) Code::Readonly | (1 << 8)),
        ReadonlyCantLock = ((int) Code::Readonly | (2 << 8)),
        ReadonlyRollback = ((int) Code::Readonly | (3 << 8)),
        ReadonlyDatabaseMoved = ((int) Code::Readonly | (4 << 8)),
        ReadonlyCantInit = ((int) Code::Readonly | (5 << 8)),
        ReadonlyDirectory = ((int) Code::Readonly | (6 << 8)),
        AbortRollback = ((int) Code::Abort | (2 << 8)),
        ConstraintCheck = ((int) Code::Constraint | (1 << 8)),
        ConstraintCommitHook = ((int) Code::Constraint | (2 << 8)),
        ConstraintForeignKey = ((int) Code::Constraint | (3 << 8)),
        ConstraintFunction = ((int) Code::Constraint | (4 << 8)),
        ConstraintNotNull = ((int) Code::Constraint | (5 << 8)),
        ConstraintPrimaryKey = ((int) Code::Constraint | (6 << 8)),
        ConstraintTrigger = ((int) Code::Constraint | (7 << 8)),
        ConstraintUnique = ((int) Code::Constraint | (8 << 8)),
        ConstraintVirtualTable = ((int) Code::Constraint | (9 << 8)),
        ConstraintRowID = ((int) Code::Constraint | (10 << 8)),
        NoticeRecoverWal = ((int) Code::Notice | (1 << 8)),
        NoticeRecoverRollback = ((int) Code::Notice | (2 << 8)),
        WarningAutoIndex = ((int) Code::Warning | (1 << 8)),
        AuthorizationUser = ((int) Code::Authorization | (1 << 8)),
        OKLoadPermanently = ((int) Code::OK | (1 << 8)),
    };

    static ExtCode rc2ec(int rc);

#pragma mark - Initialize
public:
    Error();
    Error(Code code);
    Error(Code code, const String &message);

    void clear();

#pragma mark - Info
public:
    String message;

    class Infos final {
    public:
#if __cplusplus > 201402L
#warning TODO \
std::any is available since C++17.
#endif
        template<typename T>
        typename std::enable_if<std::is_integral<T>::value, void>::type
        set(const String &key, const T &value)
        {
            m_integers[key] = (int64_t) value;
        }
        template<typename T>
        typename std::enable_if<std::is_floating_point<T>::value, void>::type
        set(const String &key, const T &value)
        {
            m_doubles[key] = (double) value;
        }
        void set(const String &key, const String &value);
        void unset(const String &key);

        const std::map<String, int64_t> &getIntegers() const;
        const std::map<String, String> &getStrings() const;
        const std::map<String, double> &getDoubles() const;

        void clear();
        bool empty() const;

    protected:
        std::map<String, int64_t> m_integers;
        std::map<String, double> m_doubles;
        std::map<String, String> m_strings;
    };
    Infos infos;

#pragma mark - Descritpion
public:
    String getDescription() const;
};

} //namespace WCDB

#endif /* __WCDB_ERROR_HPP */
