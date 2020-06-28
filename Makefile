clean_all:
	$(MAKE) -C ./lcd/ clean_all
	$(MAKE) -C ./adc/ clean_all
	$(MAKE) -C ./gpio_input/ clean_all
	$(MAKE) -C ./interrupts/ clean_all
	$(MAKE) -C ./uart_test/ clean_all
	$(MAKE) -C ./blink/ clean_all
	$(MAKE) -C ./timers_counters/ clean_all
# all:
# 	$(MAKE) -C ./lcd/ all
# 	$(MAKE) -C ./adc/ all
# 	$(MAKE) -C ./gpio_input/ all
# 	$(MAKE) -C ./interrupts/ all
# 	$(MAKE) -C ./uart_test/ all
# 	$(MAKE) -C ./blink/ all
