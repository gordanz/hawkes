import os

project_dir = "~/hawkes/"
executable = project_dir+"build/simulate_hawkes"
output_dir = project_dir+"output/"

def scaled_a(n, alpha):
    if (alpha > 1):
        exponent = -1
    else:
        exponent = -alpha
    return( 1-n**exponent)

def run_simulation( n, alpha, ndiv, nsim, nthr ):
    sigma_0 = 1.0; mu_0=1.0;
    a = scaled_a(n,alpha)
    mu = mu_0*n;
    sigma = sigma_0/n; 
    output_subdir = output_dir+f"n={n}_alpha={alpha}_nsim={nsim*nthr}/"
    os.system("mkdir -p "+output_subdir);
    command = f"{executable}" + \
        f" -d {output_subdir}" + \
        f" -a {a}" + \
        f" -l {alpha}" + \
        f" -s {sigma}" + \
        f" -m {mu}" + \
        f" -D {ndiv}" + \
        f" -S {nsim}" + \
        f" -T {nthr}"
    print(f"  Running command {command}")
    os.system(command)
    os.system(f"rm {output_subdir}/*_*")

ndiv = 1000; nsim=1; nthr=8; 


# ns = [100]
# alphas = [ 0.1, 0.3, 0.5, 0.7, 0.9, 1.1, 1.3, 2.0]
# for n in ns:
#     for alpha in alphas:
#         run_simulation( n, alpha, ndiv, nsim, nthr)

run_simulation( n=1000, alpha=0.7, ndiv=1000, nsim=100, nthr=8)




