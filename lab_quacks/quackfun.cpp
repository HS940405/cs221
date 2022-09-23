/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

    /**
     * Sums items in a stack.
     * @param s A stack holding values to sum.
     * @return The sum of all the elements in the stack, leaving the original
     *  stack in the same state (unchanged).
     *
     * @note You may modify the stack as long as you restore it to its original
     *  values.
     * @note You may use only two local variables of type T in your function.
     *  Note that this function is templatized on the stack's type, so stacks of
     *  objects overloading the + operator can be summed.
     * @note We are using the Standard Template Library (STL) stack in this
     *  problem. Its pop function works a bit differently from the stack we
     *  built. Try searching for "stl stack" to learn how to use it.
     * @hint Think recursively!
     */
    template <typename T>
    T sum(stack<T>& s)
    {
        if (s.size() == 0) return T();

        T n = s.top();
        s.pop();
        T t = n + sum(s);
        s.push(n);
        return t;

        //if (s.empty()) return T();

        //T top = s.top();
        //s.pop();
        //T total = top + sum(s);
        //s.push(top);
        //return total;
    }

    /**
     * Reverses even sized blocks of items in the queue. Blocks start at size
     * one and increase for each subsequent block.
     * @param q A queue of items to be scrambled
     *
     * @note Any "leftover" numbers should be handled as if their block was
     *  complete.
     * @note We are using the Standard Template Library (STL) queue in this
     *  problem. Its pop function works a bit differently from the stack we
     *  built. Try searching for "stl stack" to learn how to use it.
     * @hint You'll want to make a local stack variable.
     */
    template <typename T>
    void scramble(queue<T>& q)
    {
        stack<T> s;
        queue<T> q2;
        // optional: queue<T> q2;
        int num = 1;

        int size = q.size();

        while (size >= num) {
            if (num % 2 == 0) {
                for (int i = 0; i < num; i++) {
                    T tmp = q.front();
                    s.push(tmp);
                    q.pop();
                }
                
                for (int i = 0; i < num; i++) {
                    T tmp = s.top();
                    s.pop();
                    q2.push(tmp);
                }

            } else {
                for (int i = 0; i < num; i++) {
                    int tmp = q.front();
                    q.pop();
                    q2.push(tmp);
                }

                
            }

            size = size - num; 
            num++;             
        }

        if (num % 2 == 0) {
            for (int i = 0; i < size; i++) {
                T tmp = q.front();
                s.push(tmp);
                q.pop();
            }

            for (int i = 0; i < size; i++) {
                T tmp = s.top();
                s.pop();
                q2.push(tmp);
            }
        } else {
            for (int i = 0; i < size; i++) {
                T tmp = q.front();
                q.pop();
                q2.push(tmp);
            }
        }

        q = q2;

        //TA CODE
        // stack<T> s;

        // int counter = q.size();

        // for (int blocksize = 1; counter != 0; blocksize++) {
        //     if (blocksize%2) {
        //         for (int i = 0; i < blocksize && counter != 0; i++) {
        //             q.push(q.front());
        //             q.pop();
        //             counter--;
        //         }
        //     } else {
        //         for (int i = 0; i < blocksize && counter != 0; i++) {
        //             s.push(q.front());
        //             q.pop();
        //             counter--;
        //         }

        //         while (!s.empty()) {
        //             q.push(s.top());
        //             s.pop();
        //         }
        //     }
        // }

    }

    /**
     * @return true if the parameter stack and queue contain only elements of
     *  exactly the same values in exactly the same order; false, otherwise.
     *
     * @note You may assume the stack and queue contain the same number of items!
     * @note There are restrictions for writing this function.
     * - Your function may not use any loops
     * - In your function you may only declare ONE local boolean variable to use in
     *   your return statement, and you may only declare TWO local variables of
     *   parametrized type T to use however you wish.
     * - No other local variables can be used.
     * - After execution of verifySame, the stack and queue must be unchanged. Be
     *   sure to comment your code VERY well.
     */
    template <typename T>
    bool verifySame(stack<T>& s, queue<T>& q)
    {
        if (s.size() != q.size()) {
            return false;
        }

        stack<T> s2;

        int size = s.size();
        for (int i = 0; i < size; i++) {
            T n = s.top();
            s.pop();
            s2.push(n);
            s.push(n);
        }

        for (int i = 0; i < size; i++) {
            if (s2.top() != q.front()) {
                return false;
            }
        }

        return true;
    }
}
