#include <bits/stdc++.h>
using namespace std;

class RateLimiterStrategy
{
public:
    virtual bool allowRequest(const string &userId) = 0;
    virtual ~RateLimiterStrategy() {}
};

class TokenBucket : public RateLimiterStrategy
{
private:
    unordered_map<string, double> tokens;
    unordered_map<string, chrono::steady_clock::time_point> lastRefill;
    int capacity;
    double refillRate;

public:
    TokenBucket(int cap, double rate)
        : capacity(cap), refillRate(rate) {}

    bool allowRequest(const string &userId) override
    {
        auto now = chrono::steady_clock::now();

        if (!lastRefill.count(userId))
        {
            tokens[userId] = capacity;
            lastRefill[userId] = now;
        }

        double elapsed =
            chrono::duration_cast<chrono::duration<double>>(now - lastRefill[userId]).count();

        tokens[userId] = min(
            (double)capacity,
            tokens[userId] + elapsed * refillRate);

        lastRefill[userId] = now;

        if (tokens[userId] >= 1.0)
        {
            tokens[userId] -= 1.0;
            return true;
        }
        return false;
    }
};

class LeakyBucket : public RateLimiterStrategy
{
private:
    unordered_map<string, int> reqs;
    unordered_map<string, chrono::steady_clock::time_point> lastLeak;
    int capacity;
    double leakRate;

public:
    LeakyBucket(int cap, double rate)
        : capacity(cap), leakRate(rate) {}

    bool allowRequest(const string &userId) override
    {
        auto now = chrono::steady_clock::now();

        if (!lastLeak.count(userId))
        {
            reqs[userId] = 0;
            lastLeak[userId] = now;
        }

        double elapsed =
            chrono::duration_cast<chrono::duration<double>>(
                now - lastLeak[userId])
                .count();

        int leaked = elapsed * leakRate;
        reqs[userId] = max(0, reqs[userId] - leaked);
        lastLeak[userId] = now;

        if (reqs[userId] < capacity)
        {
            reqs[userId]++;
            return true;
        }
        return false;
    }
};

class FixedWindow : public RateLimiterStrategy
{
private:
    unordered_map<string, int> counter;
    unordered_map<string, time_t> windowStart;
    int limit;
    int windowSize;

public:
    FixedWindow(int lim, int window)
        : limit(lim), windowSize(window) {}

    bool allowRequest(const string &userId) override
    {
        time_t now = time(nullptr);

        if (!windowStart.count(userId) ||
            now - windowStart[userId] >= windowSize)
        {
            counter[userId] = 0;
            windowStart[userId] = now;
        }

        if (counter[userId] < limit)
        {
            counter[userId]++;
            return true;
        }
        return false;
    }
};

class SlidingWindow : public RateLimiterStrategy
{
private:
    unordered_map<string, deque<chrono::steady_clock::time_point>> requests;
    int limit;
    int windowSeconds;

public:
    SlidingWindow(int lim, int window)
        : limit(lim), windowSeconds(window) {}

    bool allowRequest(const string &userId) override
    {
        auto now = chrono::steady_clock::now();
        auto &q = requests[userId];

        while (!q.empty() &&
               chrono::duration_cast<chrono::seconds>(
                   now - q.front())
                       .count() >= windowSeconds)
        {
            q.pop_front();
        }

        if ((int)q.size() < limit)
        {
            q.push_back(now);
            return true;
        }
        return false;
    }
};

class Server
{
private:
    RateLimiterStrategy *strategy;

public:
    Server(RateLimiterStrategy *st) : strategy(st) {}

    void handleRequest(const string &userId)
    {
        if (strategy->allowRequest(userId))
        {
            cout << "Request accepted for " << userId << endl;
        }
        else
        {
            cout << "Request rejected for " << userId << endl;
        }
    }
};

int main()
{
    RateLimiterStrategy *tokenBucket = new TokenBucket(5, 1.0);
    Server server(tokenBucket);

    string user = "bindu satya";

    server.handleRequest(user);
    server.handleRequest(user);
    server.handleRequest(user);
    server.handleRequest(user);
    server.handleRequest(user);
    server.handleRequest(user);
}