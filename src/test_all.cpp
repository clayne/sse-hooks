/**
 * @file test_all.cpp
 * @brief Implementing the main test driver
 * @internal
 *
 * This file is part of SSE Hooks project (aka SSEH).
 *
 *   SSEH is free software: you can redistribute it and/or modify it
 *   under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   SSEH is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with SSEH. If not, see <http://www.gnu.org/licenses/>.
 *
 * @endinternal
 *
 * @ingroup Public API
 *
 * @details
 * n / a
 */

#include <sse-hooks/sse-hooks.h>
#include <nlohmann/json.hpp>

#include <iostream>

//--------------------------------------------------------------------------------------------------

static void trials ()
{
    using namespace std;
    using nlohmann::json;
    typedef json::json_pointer json_pointer;

    auto j = R"(
{
    "_comment": "Keys prefixed with underscore are not actually part of the document.",

    "SSEH" : {
        "version": "1.0.0"
    },

    "map" :
    {
        "GetWindowText@user32":
        {
            "_comment": "Module based detours are remembered too",

            "target" : "0x12000",
            "detours":
            {
                "0x120fff00":
                {
                    "original": "0x80020"
                }
            }
        }
    }
}
        )"_json;

    cout << j.at (json_pointer ("")) << endl;
}

//--------------------------------------------------------------------------------------------------

/// Test whether we will crash with nullptr arguments
static bool test_sseh_version ()
{
    int a, m, i;
    const char* b;
    sseh_version (nullptr, nullptr, nullptr, nullptr);
    sseh_version (&a, nullptr, nullptr, nullptr);
    sseh_version (&a, &m, nullptr, nullptr);
    sseh_version (&a, &a, &a, nullptr);
    sseh_version (nullptr, &m, &m, &b);
    a = m = i = -1; b = nullptr;
    sseh_version (&a, &m, &i, &b);
    return a >= 0 && m >= 0 && i >= 0 && b;
}

//--------------------------------------------------------------------------------------------------

int main ()
{
    int ret = 0;
    ret += test_sseh_version ();
    trials ();
    return ret;
}

//--------------------------------------------------------------------------------------------------

