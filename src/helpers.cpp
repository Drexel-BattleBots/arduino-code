unsigned long chokeServoPWM(unsigned long pwmValue, unsigned long midpoint, float boundary) {
    return pwmValue < midpoint ? midpoint - (midpoint - pwmValue) * boundary : midpoint + (pwmValue - midpoint) * boundary;
}

unsigned long chokePWM(unsigned long pwmValue, float boundary) {
    return pwmValue * boundary;
}