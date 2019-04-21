double psiconvt(double psi)
{
                bool olderror = psisenserror;
                double c1;
                double c2;
                double val = 0;
                c1 = psi * 0.004883;
                /*
                                The psi sensor starts at 0.5V – anything less is an error with the sensor
                                The psi sensor ends at 4.5V – anything more is an error with the sensor
                                Therefore, if it is outside of those parameters, throw an error
                */
                if(c1 < 0.46)
                {
                                psisenserror = true;
                }
                else if(c1 > 4.54)
                {
                                psisenserror = true;
                }
                else
                {
                                psisenserror = false;
                }
                c2 = c1 – 0.5;
                val = c2 * 50;
                return val;
}