from typing import List

class Solution:
    def colorBorder(self, grid: List[List[int]], r0: int, c0: int, color: int) -> List[List[int]]:
        x_dis = [1, -1, 0, 0]
        y_dis = [0, 0, 1, -1]
        went = [[r0,c0,grid[r0][c0]]]
        isPass = []
        for i in range(len(grid)):
            isPass.append([])
            for j in range(len(grid[i])):
                isPass[i].append(0)
        while went:
            pos = went.pop()
            t = 0
            isPass[pos[0]][pos[1]] = -1
            for i in range(4):
                x = pos[0] + x_dis[i]
                y = pos[1] + y_dis[i]
                if x >= 0 and y >= 0 and x < len(grid) and y < len(grid[x]) and grid[x][y] == pos[2] and isPass[x][y] == 0:
                    t = t + 1
                    went.append([x,y,grid[x][y]])
                elif x >= 0 and y >= 0 and x < len(grid) and y < len(grid[x]) and grid[x][y] == pos[2] and (isPass[x][y] == -1 or isPass[x][y] == color):
                    t = t + 1
            if t != 4:
                isPass[pos[0]][pos[1]] = color
        for i in range(len(grid)):
            for j in range(len(grid[i])):
                if isPass[i][j] == color:
                    grid[i][j] = color
        return grid

if __name__ == '__main__':
    s = Solution()
    grid = [[2,1,3,2,1,1,2],[1,2,3,1,2,1,2],[1,2,1,2,2,2,2],[2,1,2,2,2,2,2],[2,3,3,3,2,1,2]]
    grid = s.colorBorder(grid , 4, 4, 3)
    print(grid)