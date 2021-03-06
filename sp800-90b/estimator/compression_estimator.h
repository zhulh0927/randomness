/**
 * The MIT License
 *
 * Copyright (c) 2020 Ilwoong Jeong (https://github.com/ilwoong)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __RANDOMNESS_SP800_90B_ESTIMATOR_COMPRESSION_H__
#define __RANDOMNESS_SP800_90B_ESTIMATOR_COMPRESSION_H__

#include "entropy_estimator.h"

namespace randomness { namespace sp800_90b { namespace estimator {

    class CompressionEstimator : public EntropyEstimator 
    {
    private:
        size_t blockLength = 6;
        size_t countBlocks;
        size_t countInitBlocks = 1000;
        size_t countTestBlocks;

    public:
        std::string Name() const override;
        double Estimate() override;

    private:
        double EvaluateBinarySearch(double arg1, double arg2) const;
        double G(double z) const;
        double CalculateMean();
    };
}}}

#endif