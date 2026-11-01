class Solution:
    def isValid(self, s: str) -> bool:
        stack = []
        close_to_open = {")": "(", "]": "[", "}": "{"}

        for symb in s:
            if symb in close_to_open:
                if stack and stack[-1] == close_to_open[symb]:
                    stack.pop()
                else:
                    return False
            else:
                stack.append(symb)

        return not stack