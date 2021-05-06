#include "git2.h"
#include <iostream>
#include <string>
#include <string_view>
#include <cassert>

void PrintGitError(std::string_view Reason, int ErrorCode) {
  const git_error *e = git_error_last();
  std::cerr << Reason
     << ", error code: " << ErrorCode
     << ", error class: " << e->klass
     << ", error message: " << e->message << "\n";
}

int main(int Argc, char **Argv) {
  if (Argc < 2) {
    std::cout << "Usage: <exec> <repo_path>" << std::endl;
    return 1;
  }

  git_libgit2_init();
  git_repository *Repo = nullptr;
  {
    int error = git_repository_open(&Repo, Argv[1]);
    if (error < 0) {
      PrintGitError("git_repository_open failed", error);
      return 1;
    }
  }

  git_object *HeadObj = nullptr;
  {
    int error = git_revparse_single(&HeadObj, Repo, "HEAD");
    if (error < 0) {
      PrintGitError("git_revparse_single failed", error);
      return 1;
    }
    assert(git_object_type(HeadObj) == GIT_OBJECT_COMMIT);
  }

  git_commit* HeadCommit = (git_commit *)HeadObj;

  git_commit *CurrentCommit = HeadCommit;
  while(true) {
    git_commit *NthParentCommit = nullptr;
    {
      int error = git_commit_nth_gen_ancestor(&NthParentCommit, CurrentCommit, 1);
      if (error < 0) {
        PrintGitError("git_commit_nth_gen_ancestor failed", error);
        return -1;
      }
    }
    const git_oid *oid = git_commit_id(NthParentCommit);
    std::string NthParentCommitHash(41, ' ');
    git_oid_tostr(NthParentCommitHash.data(), 40, oid);
    std::cout << "parent commit id: " << NthParentCommitHash << "\n";
    CurrentCommit = NthParentCommit;
  }
}
