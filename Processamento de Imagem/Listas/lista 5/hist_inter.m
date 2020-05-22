function d = hist_inter(vecA, vecB)
% HIST_INTER:   histogram intersection
% Input 
% vecA, vecB: histograms
% Output
% d : normalized histogram intersection 

vecA = vecA(:);
vecB = vecB(:);
min_sum = min(sum(vecA), sum(vecB));
d = sum( min(vecA, vecB) ) / min_sum;
endfunction