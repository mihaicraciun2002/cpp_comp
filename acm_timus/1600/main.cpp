#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>

int n;
double limit;
const double inf = 1e-9;

inline double abs(const double& arg)  {
    if(arg <= 0.0)
        return -arg;
    return arg;
}

class plane  {
    private:
    double coords[3];
    double velocities[3];

    inline double velocityDiffSquared(const plane& oth)  {
        double ans = 0;
        for(int i = 0;i < 3;i++)  {
            ans += (velocities[i] - oth.velocities[i]) * (velocities[i] - oth.velocities[i]);
        }
        return ans;
    }
    inline double derivativeNumerator(const plane& oth)  {
        double ans = 0;
        for(int i = 0;i < 3;i++)  {
            ans -= (coords[i] - oth.coords[i]) * (velocities[i] - oth.velocities[i]);
        }
        return ans;
    }
    inline double findClosestTime(const plane& oth)  {
        double denominator = this -> velocityDiffSquared(oth);
        if(abs(denominator) < inf)  {
            return 0;
        }
        double ans = this -> derivativeNumerator(oth) / denominator;
        ans = std::max(ans, 0.0);
        return ans;
    }
    public:
    inline double findDistanceAtTime(const double& time, const plane& oth)  {
        double ans = 0;
        for(int i = 0;i < 3;i++)  {
            double coordsAdd = (coords[i] - oth.coords[i]);
            double velocityAdd = (velocities[i] - oth.velocities[i]) * time;
            ans += (coordsAdd + velocityAdd) * (coordsAdd + velocityAdd);
        }
        return ans;
    }
    public:
    inline double collision(const plane& oth)  {
        const double time = this -> findClosestTime(oth);
        const double distance = this -> findDistanceAtTime(time, oth);
        if(distance > limit)  {
            return -1;
        }
        double st = 0.0, dr = time;
        while(abs(st - dr) > inf)  {
            double mid = (st + dr) / 2.0;
            if(this -> findDistanceAtTime(mid, oth) > limit)  {
                st = mid;
            }else  {
                dr = mid;
            }
        }
        return dr;
    }
    plane (const double coords[], const double velocities[])  {
        memcpy(this -> coords, coords, 3 * sizeof(double));
        memcpy(this -> velocities, velocities, 3 * sizeof(double));
    }
    plane(){}
};

std::vector <plane> planes;

#define EASY_IO 0

int main()  {
    #if EASY_IO
    freopen("aux.in", "r", stdin);
    freopen("aux.out", "w", stdout);
    #endif
    scanf("%d%lf", &n, &limit);
    limit *= limit;
    planes.push_back(plane());
    for(int i = 1;i <= n;i++)  {
        double coords[3];
        double velocities[3];
        scanf("%lf%lf%lf%lf%lf%lf", &coords[0], &coords[1], &coords[2], &velocities[0], &velocities[1], &velocities[2]);
        planes.push_back(plane(coords, velocities));
    }
    double minTime;
    int firstI, firstJ;
    bool foundOne = false;
    for(int i = 1;i <= n;i++)  {
        for(int j = i + 1;j <= n;j++)  {
            double collisionTime = planes[i].collision(planes[j]);
            if(collisionTime >= 0.0)  {
                if(!foundOne || minTime > collisionTime)  {
                    minTime = collisionTime;
                    foundOne = true;
                    firstI = i;
                    firstJ = j;
                }
            }
        }
    }
    if(foundOne)  {
        printf("ALARM!\n");
        printf("%.3lf %d %d\n", minTime, firstI, firstJ);
    }else{
        printf("OK\n");
    }
    return 0;
}