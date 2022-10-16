/*! \page contributing How to Contribute
 * ## Contributing to the Source Code
 * All contributions to the source code are welcomed and will follow the process defined below:
 * 1. Open a new issue for the change that you want to make. **Please review other open issues before creating a new issue to avoid duplication of issues.**
 *  - If you would like to add more documentation, describe the areas of the current documentation that you find to be lacking within the description of your issue. 
 *  - If your contribution addresses an existing bug, please include details about the machine your are on and the steps applicable to reproduce the bug. 
 *  - If you would like to add a new feature, please describe the new feature and alternatives that you have considered. 
 *  - Label your issue with the appropriate label(s) provided in Github.
 * 2. Create a new branch that is named exactly the same as your issue (e.g. `feature/new-feature` or `bug/bug-xxxx`). 
 *  - Complete all work related to your issue in this branch.
 * 3. Within your branch create tests for your new changes.
 *  - Tests should be written in the `project/tests/` directory. 
 *  - Each new class that your code introduces should have its own `.cc` file for testing following the naming convention: `className_test.cc`. 
 *  - New tests for existing classes should be added as one or more new text fixtures in the appropriate existing test file.
 *  - These new tests should include unit, integration, regression, and component tests (as applicable).
 * 4. When you are ready to open a review on your changes:
 *  - Merge in the latest changes from the `development` branch and open a PR named exactly the same as your issue and branch.
 *  - In the body of your PR explain your changes and provide the ouput of the test application provided in the source code. This can be done by running `make clean && make -j && ./build/test-app` from the `project/` directory.
 *  - Ensure that your code meets the style guidelines described in the `C++ Code Style Guidlines` section below.
 * 5. Respond to the approval/rejection of your PR.
 *  - If your PR was approved, complete the automatic merge of the branch into the `develop` branch.
 *  - If your PR was rejected, read the comments. 
 *   - PRs can be rejected for code that does not follow the project's style guidelines, for code that has memory leaks, for code that is overly complex or inefficient, etc. Comments will specify the reason for the rejection.
 *   - After addressing the issues that the comments of your PR mention, repeat steps 3-4 as defined above to re-enter the review process.
 * 
 * ## C++ Code Style Guidlines
 * All code in this project has followed [Google's C++ Style Guide](https://google.github.io/styleguide/cppguide.html). All new code that is introduced to the codebase should follow these guidelines except for several notable exceptions:
 *  - Private member variables should not have underscores after the member name
 *  - The names of constants should be all UPPERCASE. They should not be prefixed with a `k`.
 *  - Comments should follow Doxygen's required format.
 *  - There is no restriction to the length of any line, but keep it reasonable.
 * 
 * For the most part follow those outlined in the [Google C++ Style Guide] (https://google.github.io/styleguide/cppguide.html). There are a few specific exceptions to Google's C++ Style Guide. 
 *  For instance, while Google’s style guide is in favor of putting underscores at the end of private member variables, we do not add these additional
 *  underscores because this matches the starter code that was given to us. A similar decision was made regarding line length. The guide says that each line should have no more than 80 characters, but existing code didn’t follow this convention,
 *  and our team was not eager to make it comply. Once again, these were less deliberate decisions, and more so done to keep in line with the local conventions provided to us.
 * 
 * That said, there are some points in Google’s C++ Style Guide that our team disagreed with and decided not to follow. One of these guidelines is to precede all constant variable names with the letter k. Our team found this idea odd because it makes
 *  variable names harder to read, and the word constant doesn’t even start with a k. So, rather than following Google’s advice, we decided to make all constant variable names capitalized. Another point from Google’s style guide that we deliberately 
 *  diverge from is the commenting style. Since we’re using Doxygen to document this project, the structure of our comments contain the necessary format for Doxygen to perform its automatic documenting process, meaning our header files contain many
 *  more brief, param, and asterisks than Google’s Style Guide includes. Please read more on Doxygen's commenting format and syntax at [https://www.doxygen.nl/manual/docblocks.html](https://www.doxygen.nl/manual/docblocks.html). Finally, there’s a rule in Google’s Style Guide that exceptions aren’t allowed in their code, and while we haven’t yet felt the need to write exceptions into our project, we
 *  are not disabling their use. Google’s Guide doesn’t allow exceptions because their code base is not exception-tolerant (they’d have to convert their massive code-base to be able to deal with exceptions) but our project is much smaller, and adding 
 *  exceptions wouldn’t be such a burden. Exceptions will be reviewed on a case-by-case basis with possible alternatives being compared before exceptions are added into the code base.
 * 
 * We are willing to make additional exceptions to the style guide on a case-by-case basis as situations warrant it. Please include those details in your PR. These guidelines are just that, guidelines.
 *
 * ## Copyright
 * &copy; 2021 Laura Arias Fernandez, Michael Weiner, and Malik Khadar  All rights reserved.
 *
 */