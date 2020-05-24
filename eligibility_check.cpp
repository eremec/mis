#include "eligibility_check.h"
#include "resources.h"
#include "db.h"

bool eligibilityCheck(int coverageId) {
    Coverage cov = readCoverage(coverageId);
    Insurer ins = readInsurer(cov.insurerId);

    std::vector<std::string> activeMemberIds =
        splitStr(fileRead("eligibility_db/" + ins.name), '|');

    bool active = false;
    for (std::string memberId : activeMemberIds) {
        if (cov.memberId == memberId) {
            active = true;
        }
    }

    return active;
}
