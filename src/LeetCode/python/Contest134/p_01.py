from typing import List


class Solution:
    def numMovesStones(self, a: int, b: int, c: int) -> List[int]:
        stones = [a,b,c]
        stones.sort()
        ab = stones[1] - stones[0]
        bc = stones[2] - stones[1]
        _min = 0
        if bc == 1 and ab == 1:
            return [0,0]
        if bc == 1 or ab == 1 or bc == 2 or ab == 2:
            _min = 1
        else:
            _min = 2
        _max = bc + ab -2
        return [_min, _max]


if __name__ == '__main__':
    solution = Solution();
    r = solution.numMovesStones(1,2,5)
    print(r)