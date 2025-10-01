{$IFNDEF FPC_DOTTEDUNITS}
unit rp2350;
{$ENDIF FPC_DOTTEDUNITS}

interface
{$PACKRECORDS C}
{$GOTO ON}
{$SCOPEDENUMS ON}

{$I cortexm33.inc}

const
  SIO_BASE                     = $d0000000;
  SIO_NONSEC_BASE              = $d0020000;
  PPB_BASE                     = $e0000000;
  PPB_NONSEC_BASE              = $e0020000;
  EPPB_BASE                    = $e0080000;
  SRAM_BASE                    = $20000000;
  SRAM_STRIPED_BASE            = $20000000;
  SRAM0_BASE                   = $20000000;
  SRAM4_BASE                   = $20040000;
  SRAM_STRIPED_END             = $20080000;
  SRAM8_BASE                   = $20080000;
  SRAM9_BASE                   = $20081000;
  SRAM_END                     = $20082000;
  SYSINFO_BASE                 = $40000000;
  SYSCFG_BASE                  = $40008000;
  CLOCKS_BASE                  = $40010000;
  PSM_BASE                     = $40018000;
  RESETS_BASE                  = $40020000;
  IO_BANK0_BASE                = $40028000;
  IO_QSPI_BASE                 = $40030000;
  PADS_BANK0_BASE              = $40038000;
  PADS_QSPI_BASE               = $40040000;
  XOSC_BASE                    = $40048000;
  PLL_SYS_BASE                 = $40050000;
  PLL_USB_BASE                 = $40058000;
  ACCESSCTRL_BASE              = $40060000;
  BUSCTRL_BASE                 = $40068000;
  UART0_BASE                   = $40070000;
  UART1_BASE                   = $40078000;
  SPI0_BASE                    = $40080000;
  SPI1_BASE                    = $40088000;
  I2C0_BASE                    = $40090000;
  I2C1_BASE                    = $40098000;
  ADC_BASE                     = $400a0000;
  PWM_BASE                     = $400a8000;
  TIMER0_BASE                  = $400b0000;
  TIMER1_BASE                  = $400b8000;
  HSTX_CTRL_BASE               = $400c0000;
  XIP_CTRL_BASE                = $400c8000;
  XIP_QMI_BASE                 = $400d0000;
  WATCHDOG_BASE                = $400d8000;
  BOOTRAM_BASE                 = $400e0000;
  ROSC_BASE                    = $400e8000;
  TRNG_BASE                    = $400f0000;
  SHA256_BASE                  = $400f8000;
  POWMAN_BASE                  = $40100000;
  TICKS_BASE                   = $40108000;
  OTP_BASE                     = $40120000;
  OTP_DATA_BASE                = $40130000;
  OTP_DATA_RAW_BASE            = $40134000;
  OTP_DATA_GUARDED_BASE        = $40138000;
  OTP_DATA_RAW_GUARDED_BASE    = $4013c000;
  CORESIGHT_PERIPH_BASE        = $40140000;
  CORESIGHT_ROMTABLE_BASE      = $40140000;
  CORESIGHT_AHB_AP_CORE0_BASE  = $40142000;
  CORESIGHT_AHB_AP_CORE1_BASE  = $40144000;
  CORESIGHT_TIMESTAMP_GEN_BASE = $40146000;
  CORESIGHT_ATB_FUNNEL_BASE    = $40147000;
  CORESIGHT_TPIU_BASE          = $40148000;
  CORESIGHT_CTI_BASE           = $40149000;
  CORESIGHT_APB_AP_RISCV_BASE  = $4014a000;
  GLITCH_DETECTOR_BASE         = $40158000;
  TBMAN_BASE                   = $40160000;
  DMA_BASE                     = $50000000;
  DMADEBUG_BASE                = $50000800;
  USBCTRL_DPRAM_BASE           = $50100000;
  USBCTRL_REGS_BASE            = $50110000;
  PIO0_BASE                    = $50200000;
  PIO1_BASE                    = $50300000;
  PIO2_BASE                    = $50400000;
  XIP_AUX_BASE                 = $50500000;
  HSTX_BASE                    = $50600000;

const
  clk_gpout0 = 0;
  clk_gpout1 = 1;
  clk_gpout2 = 2;
  clk_gpout3  =3;
  clk_ref = 4;
  clk_sys = 5;
  clk_peri = 6;
  clk_hstx = 7;
  clk_usb = 8;
  clk_adc = 9;

  NMI_IRQn          = -14;
  HardFault_IRQn    = -13;
  SVC_IRQn          = -5;
  PendSV_IRQn       = -2;
  SysTick_IRQn      = -1;
  TIMER0_IRQ_0      = 0;
  TIMER0_IRQ_1      = 1;
  TIMER0_IRQ_2      = 2;
  TIMER0_IRQ_3      = 3;
  TIMER1_IRQ_0      = 4;
  TIMER1_IRQ_1      = 5;
  TIMER1_IRQ_2      = 6;
  TIMER1_IRQ_3      = 7;
  PWM_IRQ_WRAP_0    = 8;
  PWM_IRQ_WRAP_1    = 9;
  DMA_IRQ_0         = 10;
  DMA_IRQ_1         = 11;
  DMA_IRQ_2         = 12;
  DMA_IRQ_3         = 13;
  USBCTRL_IRQ       = 14;
  PIO0_IRQ_0        = 15;
  PIO0_IRQ_1        = 16;
  PIO1_IRQ_0        = 17;
  PIO1_IRQ_1        = 18;
  PIO2_IRQ_0        = 19;
  PIO2_IRQ_1        = 20;
  IO_IRQ_BANK0      = 21;
  IO_IRQ_BANK0_NS   = 22;
  IO_IRQ_QSPI       = 23;
  IO_IRQ_QSPI_NS    = 24;
  SIO_IRQ_FIFO      = 25;
  SIO_IRQ_BELL      = 26;
  SIO_IRQ_FIFO_NS   = 27;
  SIO_IRQ_BELL_NS   = 28;
  SIO_IRQ_MTIMECMP  = 29;
  CLOCKS_IRQ        = 30;
  SPI0_IRQ          = 31;
  SPI1_IRQ          = 32;
  UART0_IRQ         = 33;
  UART1_IRQ         = 34;
  ADC_IRQ_FIFO      = 35;
  I2C0_IRQ          = 36;
  I2C1_IRQ          = 37;
  OTP_IRQ           = 38;
  TRNG_IRQ          = 39;
  PROC0_IRQ_CTI     = 40;
  PROC1_IRQ_CTI     = 41;
  PLL_SYS_IRQ       = 42;
  PLL_USB_IRQ       = 43;
  POWMAN_IRQ_POW    = 44;
  POWMAN_IRQ_TIMER  = 45;

type

  TINTERP_Registers = record
    accum : array[0..1] of longword;
    base : array[0..2] of longword;
    pop : array[0..2] of longword;
    peek : array[0..2] of longword;
    ctrl : array[0..1] of longword;
    add_raw : array[0..1] of longword;
    base01 : longword;
  end;

  TSIO_Registers = record
    CPUID: longword;
    GPIO_IN: longword;
    GPIO_HI_IN: longword;
    Reserved1: longword;
    GPIO_OUT: longword;
    GPIO_HI_OUT: longword;
    GPIO_OUT_SET: longword;
    GPIO_HI_OUT_SET: longword;
    GPIO_OUT_CLR: longword;
    GPIO_HI_OUT_CLR: longword;
    GPIO_OUT_XOR: longword;
    GPIO_HI_OUT_XOR: longword;
    GPIO_OE: longword;
    GPIO_HI_OE: longword;
    GPIO_OE_SET: longword;
    GPIO_HI_OE_SET: longword;
    GPIO_OE_CLR: longword;
    GPIO_HI_OE_CLR: longword;
    GPIO_OE_XOR: longword;
    GPIO_HI_OE_XOR: longword;
    FIFO_ST: longword;
    FIFO_WR: longword;
    FIFO_RD: longword;
    SPINLOCK_ST: longword;
    Reserved2: array[0..7] of longword;
    INTERP: array[0..1] of TINTERP_Registers;
    SPINLOCK: array[0..31] of longword;
    DOORBELL_OUT_SET: longword;
    DOORBELL_OUT_CLR: longword;
    DOORBELL_IN_SET: longword;
    Reserved3: longword;
    PERI_NONSEC: longword;
    Reserved4: array[0..3] of longword;
    RISCV_SOFTIRQ: longword;
    MTIME_CTRL: longword;
    Reserved5: array[0..1] of longword;
    MTIME: longword;
    MTIMEH: longword;
    MTIMECMP: longword;
    MTIMECMPH: longword;
    TMDS_CTRL: longword;
    TMDS_WDATA: longword;
    TMDS_PEEK_SINGLE: longword;
    TMDS_POP_SINGLE: longword;
    TMDS_PEEK_DOUBLE_L0: longword;
    TMDS_POP_DOUBLE_L0: longword;
    TMDS_PEEK_DOUBLE_L1: longword;
    TMDS_POP_DOUBLE_L1: longword;
    TMDS_PEEK_DOUBLE_L2: longword;
    TMDS_POP_DOUBLE_L: longword;
  end;

  TACCESSCTRL_Registers = record
    LOCK: longword;
    FORCE_CORE_NS: longword;
    CFGRESET: longword;
    GPIO_NSMASK0: longword;
    GPIO_NSMASK1: longword;
    ROM: longword;
    XIP_MAIN: longword;
    SRAM: array[0..9] of longword;
    DMA: longword;
    USBCTRL: longword;
    PIO0: longword;
    PIO1: longword;
    PIO2: longword;
    CORESIGHT_TRACE: longword;
    CORESIGHT_PERIPH: longword;
    SYSINFO: longword;
    RESETS: longword;
    IO_BANK0: longword;
    IO_BANK1: longword;
    PADS_BANK0: longword;
    PADS_QSPI: longword;
    BUSCTRL: longword;
    ADC: longword;
    HSTX: longword;
    I2C0: longword;
    I2C1: longword;
    PWM: longword;
    SPI0: longword;
    SPI1: longword;
    TIMER0: longword;
    TIMER1: longword;
    UART0: longword;
    UART1: longword;
    OTP: longword;
    TBMAN: longword;
    POWMAN: longword;
    TRNG: longword;
    SHA256: longword;
    SYSCFG: longword;
    CLOCKS: longword;
    XOSC: longword;
    ROSC: longword;
    PLL_SYS: longword;
    PLL_USB: longword;
    TICKS: longword;
    WATCHDOG: longword;
    PSM: longword;
    XIP_CTRL: longword;
    XIP_QMI: longword;
    XIP_AUX: longword;
  end;

  TPADSBANK0_Registers = record
    voltage_select : longword;
    io : array[0..47] of longword;
    swclk: longword;
    swd: longword;
  end;

  TIOIRQCTRL_Registers = record
    inte : array[0..5] of longword;
    intf : array[0..5] of longword;
    ints : array[0..5] of longword;
  end;

  TIOBANK0_Registers = record
    io : array[0..47] of record
      status : longword;
      ctrl : longword;
    end;
    reserved: array[0..31] of longword;
    IRQSUMMARY_PROC0_SECURE0: longword;
    IRQSUMMARY_PROC0_SECURE1: longword;
    IRQSUMMARY_PROC0_NONSECURE0: longword;
    IRQSUMMARY_PROC0_NONSECURE1: longword;
    IRQSUMMARY_PROC1_SECURE0: longword;
    IRQSUMMARY_PROC1_SECURE1: longword;
    IRQSUMMARY_PROC1_NONSECURE0: longword;
    IRQSUMMARY_PROC1_NONSECURE1: longword;
    IRQSUMMARY_COMA_WAKE_SECURE: longword;
    IRQSUMMARY_COMA_WAKE_NONSECURE: longword;
    intr: array[0..5] of longword;
    proc: array[0..1] of TIOIRQCTRL_Registers;
    dormant_wake: TIOIRQCTRL_Registers;
  end;

  TIOQSPI_Registers = record
    status: longword;
    ctrl: longword;
  end;

  TIOQSPIBANK_Registers = record
    usbphy_dp: TIOQSPI_Registers;
    usbphy_dm: TIOQSPI_Registers;
    gpio_qspi_sclk: TIOQSPI_Registers;
    gpio_qspi_ss: TIOQSPI_Registers;
    gpio_qspi_sd: array[0..3] of TIOQSPI_Registers;
    reserved: array[0..111] of longword;
    irqsummary: array[0..5] of longword;
    intr: longword;
    proc: array[0..1] of TIOIRQCTRL_Registers;
    dormant_wake: TIOIRQCTRL_Registers;
  end;

  TPADSQSPI_Registers = record
    voltage_select : longword;
    sclk: longword;
    sd: array[0..3] of longword;
    ss: longword;
  end;

  PCLOCK_Registers = ^TCLOCK_Registers;
  TCLOCK_Registers = record
    ctrl : longword;
    &div : longword;
    selected : longword;
  end;

  PFC_Registers = ^TFC_Registers;
  TFC_Registers = record
    ref_khz : longword;
    min_khz : longword;
    max_khz : longword;
    delay : longword;
    interval : longword;
    src : longword;
    status : longword;
    result : longword;
  end;

  TCLOCKS_Registers = record
    clk_gpout : array[0..3] of TCLOCK_Registers;
    clk_ref : TCLOCK_Registers;
    clk_sys : TCLOCK_Registers;
    clk_peri : TCLOCK_Registers;
    clk_hstx : TCLOCK_Registers;
    clk_usb : TCLOCK_Registers;
    clk_adc : TCLOCK_Registers;
    DFTCLK: record
      XOSC_CTRL: longword;
      ROSC_CTRL: longword;
      LPOSC_CTRL: longword;
    end;
    clk_sys_resus : record
      ctrl : longword;
      status : longword;
    end;
    fc0 : TFC_Registers;
    wake_en: array[0..1] of longword;
    sleep_en: array[0..1] of longword;
    enabled: array[0..1] of longword;
    intr : longword;
    inte : longword;
    intf : longword;
    ints : longword;
  end;

  TCLOCKS_Registers_alt = record
    clk: array[0..9] of TCLOCK_Registers; // Array of clock configurations
    DFTCLK: record
      XOSC_CTRL: longword;
      ROSC_CTRL: longword;
      LPOSC_CTRL: longword;
    end;
    clk_sys_resus : record
      ctrl : longword;
      status : longword;
    end;
    fc0 : TFC_Registers;
    wake_en: array[0..1] of longword;
    sleep_en: array[0..1] of longword;
    enabled: array[0..1] of longword;
    intr : longword;
    inte : longword;
    intf : longword;
    ints : longword;
  end;

  TTICK_Registers = record
    ctrl: longword;
    cycles: longword;
    count: longword;
  end;

  TTICKS_Registers = record
    case byte of
    0: (tick: array[0..5] of TTick_Registers);
    1: (proc0: TTick_Registers;
        proc1: TTick_Registers;
        timer0: TTick_Registers;
        timer1: TTick_Registers;
        watchdog: TTick_Registers;
        riscv: TTick_Registers);
  end;

type
  TADC_Registers = record
    cs : longword;
    result : longword;
    fcs : longword;
    fifo : longword;
    &div : longword;
    intr : longword;
    inte : longword;
    intf : longword;
    ints : longword;
  end;

  TBUSCTRL_Registers = record
    priority : longword;
    priority_ack : longword;
    perfctrl_en: longword;
    perf : array[0..3] of record
      ctr : longword;
      sel : longword;
    end;
  end;

  TDMACHANNEL_Registers = record
    read_addr : longword;
    write_addr : longword;
    transfer_count : longword;
    ctrl_trig : longword;
    al1_ctrl : longword;
    al1_read_addr : longword;
    al1_write_addr : longword;
    al1_transfer_count_trig : longword;
    al2_ctrl : longword;
    al2_transfer_count : longword;
    al2_read_addr : longword;
    al2_write_addr_trig : longword;
    al3_ctrl : longword;
    al3_write_addr : longword;
    al3_transfer_count : longword;
    al3_read_addr_trig : longword;
  end;

  TDMA_Registers = record
    ch : array[0..15] of TDMACHANNEL_Registers;
    intr : longword;
    inte0 : longword;
    intf0 : longword;
    ints0 : longword;
    RESERVED0 : longword;
    inte1 : longword;
    intf1 : longword;
    ints1 : longword;
    RESERVED1 : longword;
    inte2 : longword;
    intf2 : longword;
    ints2 : longword;
    RESERVED2 : longword;
    inte3 : longword;
    intf3 : longword;
    ints3 : longword;
    timer : array[0..3] of longword;
    multi_channel_trigger : longword;
    sniff_ctrl : longword;
    sniff_data : longword;
    RESERVED3 : longword;
    fifo_levels : longword;
    abort : longword;
    n_channels: longword;
    seccfg_ch: array[0..15] of longword;
    seccfg_irq: array[0..3] of longword;
    seccfg_misc: longword;
    mpu_ctrl: longword;
    mpu: array[0..7] of record
      bar: longword;
      lar: longword;
    end;
  end;

  TDMADEBUG_Registers = record
    ch : array[0..15] of record
      ctrdeq : longword;
      tcr : longword;
      RESERVED0 : array[0..13] of longword;
    end;
  end;

  TI2C_Registers = record
    con : longword;
    tar : longword;
    sar : longword;
    RESERVED0 : longword;
    data_cmd : longword;
    ss_scl_hcnt : longword;
    ss_scl_lcnt : longword;
    fs_scl_hcnt : longword;
    fs_scl_lcnt : longword;
    RESERVED1 : array[0..1] of longword;
    intr_stat : longword;
    intr_mask : longword;
    raw_intr_stat : longword;
    rx_tl : longword;
    tx_tl : longword;
    clr_intr : longword;
    clr_rx_under : longword;
    clr_rx_over : longword;
    clr_tx_over : longword;
    clr_rd_req : longword;
    clr_tx_abrt : longword;
    clr_rx_done : longword;
    clr_activity : longword;
    clr_stop_det : longword;
    clr_start_det : longword;
    clr_gen_call : longword;
    enable : longword;
    status : longword;
    txflr : longword;
    rxflr : longword;
    sda_hold : longword;
    tx_abrt_source : longword;
    slv_data_nack_only : longword;
    dma_cr : longword;
    dma_tdlr : longword;
    dma_rdlr : longword;
    sda_setup : longword;
    ack_general_call : longword;
    enable_status : longword;
    fs_spklen : longword;
    RESERVED2 : longword;
    clr_restart_det : longword;
    RESERVED3 : array[0..17] of longword;
    comp_param_1 : longword;
    comp_version : longword;
    comp_type : longword;
  end;

  TPIO_Registers = record
    ctrl : longword;
    fstat : longword;
    fdebug : longword;
    flevel : longword;
    txf : array[0..3] of longword;
    rxf : array[0..3] of longword;
    irq : longword;
    irq_force : longword;
    input_sync_bypass : longword;
    dbg_padout : longword;
    dbg_padoe : longword;
    dbg_cfginfo : longword;
    instr_mem : array[0..31] of longword;
    sm : array[0..3] of record
      clkdiv : longword;
      execctrl : longword;
      shiftctrl : longword;
      addr : longword;
      instr : longword;
      pinctrl : longword;
    end;
    rxf_putget: array[0..3,0..3] of longword;
    gpiobase: longword;
    intr : longword;
    irq0: record
      inte : longword;
      intf : longword;
      ints : longword;
    end;
    irq1: record
      inte : longword;
      intf : longword;
      ints : longword;
    end;
  end;

  TPLL_Registers = record
    cs : longword;
    pwr : longword;
    fbdiv_int : longword;
    prim : longword;
    intr: longword;
    inte: longword;
    intf: longword;
    ints: longword;
  end;

  TPSM_Registers = record
    frce_on : longword;
    frce_off : longword;
    wdsel : longword;
    done : longword;
  end;

  TPWMSLICE_Registers = record
    csr : longword;
    &div : longword;
    ctr : longword;
    cc : longword;
    top : longword;
  end;

  TPWM_Registers = record
    slice : array[0..11] of TPWMSLICE_Registers;
    en : longword;
    intr: longword;
    irq: array[0..1] of record
      inte : longword;
      intf : longword;
      ints : longword;
    end;
  end;

  TRESETS_Registers = record
    reset : longword;
    wdsel : longword;
    reset_done : longword;
  end;

  TROSC_Registers = record
    ctrl : longword;
    freqa : longword;
    freqb : longword;
    random: longword;
    dormant : longword;
    &div : longword;
    phase : longword;
    status : longword;
    randombit : longword;
    count : longword;
  end;

  TSPI_Registers = record
    cr0 : longword;
    cr1 : longword;
    dr : longword;
    sr : longword;
    cpsr : longword;
    imsc : longword;
    ris : longword;
    mis : longword;
    icr : longword;
    dmacr : longword;
  end;

  TSYSCFG_Registers = record
    proc_config : longword;
    proc_in_sync_bypass : longword;
    proc_in_sync_bypass_hi : longword;
    dbgforce : longword;
    mempowerdown : longword;
    auxctrl: longword;
  end;

  TSYSINFO_Registers = record
    chip_id : longword;
    package_sel: longword;
    platform : longword;
    reserved0 : array[0..1] of longword;
    gitref_rp2350 : longword;
  end;

  TTIMER_Registers = record
    timehw : longword;
    timelw : longword;
    timehr : longword;
    timelr : longword;
    alarm : array[0..3] of longword;
    armed : longword;
    timerawh : longword;
    timerawl : longword;
    dbgpause : longword;
    pause : longword;
    locked: longword;
    source: longword;
    intr : longword;
    inte : longword;
    intf : longword;
    ints : longword;
  end;

  TUART_Registers = record
    dr : longword;
    rsr : longword;
    RESERVED0 : array[0..3] of longword;
    fr : longword;
    RESERVED1 : longword;
    ilpr : longword;
    ibrd : longword;
    fbrd : longword;
    lcr_h : longword;
    cr : longword;
    ifls : longword;
    imsc : longword;
    ris : longword;
    mis : longword;
    icr : longword;
    dmacr : longword;
  end;
(*
  TUSBDEVICEDPRAM = record
    setup_packet : array[0..7] of byte;
    ep_ctrl : array[0..14] of record
      &in : longword;
      &out : longword;
    end;
    ep_buf_ctrl : array[0..15] of record
      &in : longword;
      &out : longword;
    end;
    ep0_buf_a : array[0..63] of byte;
    ep0_buf_b : array[0..63] of byte;
    epx_data : array[0..(4096-$180)-1] of byte;
  end;

  TUSBHOSTDPRAM = record
    setup_packet : array[0..7] of byte;
    int_ep_ctrl : array[0..14] of record
      ctrl : longword;
      spare : longword;
    end;
    epx_buf_ctrl : longword;
    _spare0 : longword;
    int_ep_buffer_ctrl : array[0..14] of record
      ctrl : longword;
      spare : longword;
    end;
    epx_ctrl : longword;
    _spare1 : array[0..123] of byte;
    epx_data : array[0..(4096-$180)-1] of byte;
  end;
*)
  TUSB_Registers = record
    dev_addr_endp: longword;
    int_ep_addr_ctrl : array[1..15] of longword;
    main_ctrl : longword;
    sof_wr : longword;
    sof_rd : longword;
    sie_ctrl : longword;
    sie_status : longword;
    int_ep_ctrl : longword;
    buf_status : longword;
    buf_cpu_should_handle : longword;
    abort : longword;
    abort_done : longword;
    ep_stall_arm : longword;
    nak_poll : longword;
    ep_nak_stall_status : longword;
    muxing : longword;
    pwr : longword;
    phy_direct : longword;
    phy_direct_override : longword;
    phy_trim : longword;
    linestate_tuning : longword;
    intr : longword;
    inte : longword;
    intf : longword;
    ints : longword;
    sof_timestamp_raw: longword;
    sof_timestamp_last: longword;
    sm_state: longword;
    ep_tx_error: longword;
    ep_rx_error: longword;
    dev_sm_watchdog: longword;
  end;
(*
  TVREGANDCHIPRESET_Registers = record
    vreg : longword;
    bod : longword;
    chip_reset : longword;
  end;
*)
  TWATCHDOG_Registers = record
    ctrl : longword;
    load : longword;
    reason : longword;
    scratch : array[0..7] of longword;
//    tick : longword;
  end;
(*
  TXIPCTRL_Registers = record
    ctrl : longword;
    flush : longword;
    stat : longword;
    ctr_hit : longword;
    ctr_acc : longword;
    stream_addr : longword;
    stream_ctr : longword;
    stream_fifo : longword;
  end;
*)
  TXOSC_Registers = record
    ctrl : longword;
    status : longword;
    dormant : longword;
    startup : longword;
    count : longword;
  end;
(*
  TMPU_Registers = record
    _type : longword;
    ctrl : longword;
    rnr : longword;
    rbar : longword;
    rasr : longword;
  end;
*)
  TSYSTICK_Registers = record
    csr : longword;
    rvr : longword;
    cvr : longword;
    calib : longword;
  end;
(*
  TSCB_Reqisters = record
    cpuid : longword;
    icsr : longword;
    vtor : longword;
    aircr : longword;
    scr : longword;
  end;
*)

var
  SysInfo : TSysInfo_Registers absolute SYSINFO_BASE;
  SysCfg : TSYSCFG_REGISTERS absolute SYSCFG_BASE;
  PSM : TPSM_Registers absolute PSM_BASE;
  SIO : TSIO_Registers absolute SIO_BASE;
  TICK : TSYSTICK_Registers absolute (PPB_BASE + SYST_CSR);
  PADSBANK0 : TPADSBANK0_Registers absolute PADS_BANK0_BASE;
  PADSQSPI : TPADSQSPI_Registers absolute PADS_QSPI_BASE;
  IOBANK0 : TIOBANK0_Registers absolute IO_BANK0_BASE;
  IOQSPI : TIOQSPI_Registers absolute IO_QSPI_BASE;
  BUSCTRL : TBUSCTRL_Registers absolute BUSCTRL_BASE;
  RESETS : TRESETS_Registers absolute RESETS_BASE;
  PLLSYS : TPLL_Registers absolute PLL_SYS_BASE;
  PLLUSB : TPLL_Registers absolute PLL_USB_BASE;
  CLOCKS : TCLOCKS_Registers absolute CLOCKS_BASE;
  _CLOCKS : TCLOCKS_Registers_ALT absolute CLOCKS_BASE;
  ROSC : TROSC_Registers absolute ROSC_BASE;
  UART0 : TUART_Registers absolute UART0_BASE;
  UART1 : TUART_Registers absolute UART1_BASE;
  SPI0 : TSPI_Registers absolute SPI0_BASE;
  SPI1 : TSPI_Registers absolute SPI1_BASE;
  I2C0 : TI2C_Registers absolute I2C0_BASE;
  I2C1 : TI2C_Registers absolute I2C1_BASE;
  PWM : TPWM_Registers absolute PWM_BASE;
  TIMER0 : TTIMER_Registers absolute TIMER0_BASE;
  TIMER1 : TTIMER_Registers absolute TIMER1_BASE;
  XOSC : TXOSC_Registers absolute XOSC_BASE;
  WATCHDOG : TWATCHDOG_Registers absolute WATCHDOG_BASE;
  TICKS: TTICKS_Registers absolute TICKS_BASE;
  ADC : TADC_Registers absolute ADC_BASE;
  ACCESSCTRL: TACCESSCTRL_Registers absolute ACCESSCTRL_BASE;
  DMA : TDMA_Registers absolute DMA_BASE;
  DMADEBUG : TDMADEBUG_Registers absolute DMADEBUG_BASE;
  USB : TUSB_Registers absolute USBCTRL_REGS_BASE;
  PIO0 : TPIO_Registers absolute PIO0_BASE;
  PIO1 : TPIO_Registers absolute PIO1_BASE;
  PIO2 : TPIO_Registers absolute PIO2_BASE;
(*
  VREGANDCHIPRESET : TVREGANDCHIPRESET_Registers absolute VREG_AND_CHIP_RESET_BASE;

*)
implementation

procedure TIMER0_IRQ_0_Handler; external name 'TIMER0_IRQ_0_Handler';
procedure TIMER0_IRQ_1_Handler; external name 'TIMER0_IRQ_1_Handler';
procedure TIMER0_IRQ_2_Handler; external name 'TIMER0_IRQ_2_Handler';
procedure TIMER0_IRQ_3_Handler; external name 'TIMER0_IRQ_3_Handler';
procedure TIMER1_IRQ_0_Handler; external name 'TIMER1_IRQ_0_Handler';
procedure TIMER1_IRQ_1_Handler; external name 'TIMER1_IRQ_1_Handler';
procedure TIMER1_IRQ_2_Handler; external name 'TIMER1_IRQ_2_Handler';
procedure TIMER1_IRQ_3_Handler; external name 'TIMER1_IRQ_3_Handler';
procedure PWM_IRQ_WRAP_0_Handler; external name 'PWM_IRQ_WRAP_0_Handler';
procedure PWM_IRQ_WRAP_1_Handler; external name 'PWM_IRQ_WRAP_1_Handler';
procedure DMA_IRQ_0_Handler; external name 'DMA_IRQ_0_Handler';
procedure DMA_IRQ_1_Handler; external name 'DMA_IRQ_1_Handler';
procedure DMA_IRQ_2_Handler; external name 'DMA_IRQ_2_Handler';
procedure DMA_IRQ_3_Handler; external name 'DMA_IRQ_3_Handler';
procedure USBCTRL_IRQ_Handler; external name ' USBCTRL_IRQ_Handler';
procedure PIO0_IRQ_0_Handler; external name 'PIO0_IRQ_0_Handler';
procedure PIO0_IRQ_1_Handler; external name 'PIO0_IRQ_1_Handler';
procedure PIO1_IRQ_0_Handler; external name 'PIO1_IRQ_0_Handler';
procedure PIO1_IRQ_1_Handler; external name 'PIO1_IRQ_1_Handler';
procedure PIO2_IRQ_0_Handler; external name 'PIO2_IRQ_0_Handler';
procedure PIO2_IRQ_1_Handler; external name 'PIO2_IRQ_1_Handler';
procedure IO_IRQ_BANK0_Handler; external name 'IO_IRQ_BANK0_Handler';
procedure IO_IRQ_BANK0_NS_Handler; external name 'IO_IRQ_BANK0_NS_Handler';
procedure IO_IRQ_QSPI_Handler; external name 'IO_IRQ_QSPI_Handler';
procedure IO_IRQ_QSPI_NS_Handler; external name 'IO_IRQ_QSPI_NS_Handler';
procedure SIO_IRQ_FIFO_Handler; external name 'SIO_IRQ_FIFO_Handler';
procedure SIO_IRQ_BELL_Handler; external name 'SIO_IRQ_BELL_Handler';
procedure SIO_IRQ_FIFO_NS_Handler; external name 'SIO_IRQ_FIFO_NS_Handler';
procedure SIO_IRQ_BELL_NS_Handler; external name 'SIO_IRQ_BELL_NS_Handler';
procedure SIO_IRQ_MTIMECMP_Handler; external name 'SIO_IRQ_MTIMECMP_Handler';
procedure CLOCKS_IRQ_Handler; external name 'CLOCKS_IRQ_Handler';
procedure SPI0_IRQ_Handler; external name 'SPI0_IRQ_Handler';
procedure SPI1_IRQ_Handler; external name 'SPI1_IRQ_Handler';
procedure UART0_IRQ_Handler; external name 'UART0_IRQ_Handler';
procedure UART1_IRQ_Handler; external name 'UART1_IRQ_Handler';
procedure ADC_IRQ_FIFO_Handler; external name 'ADC_IRQ_FIFO_Handler';
procedure I2C0_IRQ_Handler; external name 'I2C0_IRQ_Handler';
procedure I2C1_IRQ_Handler; external name 'I2C1_IRQ_Handler';
procedure OTP_IRQ_Handler; external name 'OTP_IRQ_Handler';
procedure TRNG_IRQ_Handler; external name 'TRNG_IRQ_Handler';
procedure PROC0_IRQ_CTI_Handler; external name 'PROC0_IRQ_CTI_Handler';
procedure PROC1_IRQ_CTI_Handler; external name 'PROC1_IRQ_CTI_Handler';
procedure PLL_SYS_IRQ_Handler; external name 'PLL_SYS_IRQ_Handler';
procedure PLL_USB_IRQ_Handler; external name 'PLL_USB_IRQ_Handler';
procedure POWMAN_IRQ_POW_Handler; external name 'POWMAN_IRQ_POW_Handler';
procedure POWMAN_IRQ_TIMER_Handler; external name 'POWMAN_IRQ_TIMER_Handler';

procedure InvalidIRQ; assembler; nostackframe;
asm
  bkpt #0000
end;

procedure NMI_Handler; assembler; nostackframe;
asm
  bkpt #0000
end;

procedure HardFault_Handler; assembler; nostackframe;
asm
  bkpt #0000
end;

procedure SVC_Handler; assembler; nostackframe;
asm
  bkpt #0000
end;

procedure PendSV_Handler; assembler; nostackframe;
asm
  bkpt #0000
end;

procedure SysTick_Handler; assembler; nostackframe;
asm
  bkpt #0000
end;

{$I cortexm33_start.inc}

procedure Vectors; assembler; nostackframe; public name '_vectors';
label interrupt_vectors;
asm
  .section ".init.interrupt_vectors"
  interrupt_vectors:
  .long _stack_top
  .long Startup
  .long NMI_Handler
  .long HardFault_Handler
  .long InvalidIRQ
  .long InvalidIRQ
  .long InvalidIRQ
  .long InvalidIRQ
  .long InvalidIRQ
  .long InvalidIRQ
  .long InvalidIRQ
  .long SVC_Handler
  .long InvalidIRQ
  .long InvalidIRQ
  .long PendSV_Handler
  .long SysTick_Handler
  .long TIMER0_IRQ_0_Handler      // irq0
  .long TIMER0_IRQ_1_Handler      // irq1
  .long TIMER0_IRQ_2_Handler      // irq2
  .long TIMER0_IRQ_3_Handler      // irq3
  .long TIMER1_IRQ_0_Handler      // irq4
  .long TIMER1_IRQ_1_Handler      // irq5
  .long TIMER1_IRQ_2_Handler      // irq6
  .long TIMER1_IRQ_3_Handler      // irq7
  .long PWM_IRQ_WRAP_0_Handler    // irq8
  .long PWM_IRQ_WRAP_1_Handler    // irq9
  .long DMA_IRQ_0_Handler         // irq10
  .long DMA_IRQ_1_Handler         // irq11
  .long DMA_IRQ_2_Handler         // irq12
  .long DMA_IRQ_3_Handler         // irq13
  .long USBCTRL_IRQ_Handler       // irq14
  .long PIO0_IRQ_0_Handler        // irq15
  .long PIO0_IRQ_1_Handler        // irq16
  .long PIO1_IRQ_0_Handler        // irq17
  .long PIO1_IRQ_1_Handler        // irq18
  .long PIO2_IRQ_0_Handler        // irq19
  .long PIO2_IRQ_1_Handler        // irq20
  .long IO_IRQ_BANK0_Handler      // irq21
  .long IO_IRQ_BANK0_NS_Handler   // irq22
  .long IO_IRQ_QSPI_Handler       // irq23
  .long IO_IRQ_QSPI_NS_Handler    // irq24
  .long SIO_IRQ_FIFO_Handler      // irq25
  .long SIO_IRQ_BELL_Handler      // irq26
  .long SIO_IRQ_FIFO_NS_Handler   // irq27
  .long SIO_IRQ_BELL_NS_Handler   // irq28
  .long SIO_IRQ_MTIMECMP_Handler  // irq29
  .long CLOCKS_IRQ_Handler        // irq30
  .long SPI0_IRQ_Handler          // irq31
  .long SPI1_IRQ_Handler          // irq32
  .long UART0_IRQ_Handler         // irq33
  .long UART1_IRQ_Handler         // irq34
  .long ADC_IRQ_FIFO_Handler      // irq35
  .long I2C0_IRQ_Handler          // irq36
  .long I2C1_IRQ_Handler          // irq37
  .long OTP_IRQ_Handler           // irq38
  .long TRNG_IRQ_Handler          // irq39
  .long PROC0_IRQ_CTI_Handler     // irq40
  .long PROC1_IRQ_CTI_Handler     // irq41
  .long PLL_SYS_IRQ_Handler       // irq42
  .long PLL_USB_IRQ_Handler       // irq43
  .long POWMAN_IRQ_POW_Handler    // irq44
  .long POWMAN_IRQ_TIMER_Handler  // irq45
  .long InvalidIRQ
  .long InvalidIRQ
  .long InvalidIRQ
  .long InvalidIRQ
  .long InvalidIRQ
  .long InvalidIRQ

  .weak NMI_Handler
  .weak HardFault_Handler
  .weak SVC_Handler
  .weak PendSV_Handler
  .weak SysTick_Handler
  .weak TIMER0_IRQ_0_Handler      // irq0
  .weak TIMER0_IRQ_1_Handler      // irq1
  .weak TIMER0_IRQ_2_Handler      // irq2
  .weak TIMER0_IRQ_3_Handler      // irq3
  .weak TIMER1_IRQ_0_Handler      // irq4
  .weak TIMER1_IRQ_1_Handler      // irq5
  .weak TIMER1_IRQ_2_Handler      // irq6
  .weak TIMER1_IRQ_3_Handler      // irq7
  .weak PWM_IRQ_WRAP_0_Handler    // irq8
  .weak PWM_IRQ_WRAP_1_Handler    // irq9
  .weak DMA_IRQ_0_Handler         // irq10
  .weak DMA_IRQ_1_Handler         // irq11
  .weak DMA_IRQ_2_Handler         // irq12
  .weak DMA_IRQ_3_Handler         // irq13
  .weak USBCTRL_IRQ_Handler       // irq14
  .weak PIO0_IRQ_0_Handler        // irq15
  .weak PIO0_IRQ_1_Handler        // irq16
  .weak PIO1_IRQ_0_Handler        // irq17
  .weak PIO1_IRQ_1_Handler        // irq18
  .weak PIO2_IRQ_0_Handler        // irq19
  .weak PIO2_IRQ_1_Handler        // irq20
  .weak IO_IRQ_BANK0_Handler      // irq21
  .weak IO_IRQ_BANK0_NS_Handler   // irq22
  .weak IO_IRQ_QSPI_Handler       // irq23
  .weak IO_IRQ_QSPI_NS_Handler    // irq24
  .weak SIO_IRQ_FIFO_Handler      // irq25
  .weak SIO_IRQ_BELL_Handler      // irq26
  .weak SIO_IRQ_FIFO_NS_Handler   // irq27
  .weak SIO_IRQ_BELL_NS_Handler   // irq28
  .weak SIO_IRQ_MTIMECMP_Handler  // irq29
  .weak CLOCKS_IRQ_Handler        // irq30
  .weak SPI0_IRQ_Handler          // irq31
  .weak SPI1_IRQ_Handler          // irq32
  .weak UART0_IRQ_Handler         // irq33
  .weak UART1_IRQ_Handler         // irq34
  .weak ADC_IRQ_FIFO_Handler      // irq35
  .weak I2C0_IRQ_Handler          // irq36
  .weak I2C1_IRQ_Handler          // irq37
  .weak OTP_IRQ_Handler           // irq38
  .weak TRNG_IRQ_Handler          // irq39
  .weak PROC0_IRQ_CTI_Handler     // irq40
  .weak PROC1_IRQ_CTI_Handler     // irq41
  .weak PLL_SYS_IRQ_Handler       // irq42
  .weak PLL_USB_IRQ_Handler       // irq43
  .weak POWMAN_IRQ_POW_Handler    // irq44
  .weak POWMAN_IRQ_TIMER_Handler  // irq45
  .text
end;

procedure Info_Header; assembler; nostackframe;
//label binary_info_header;
asm
  .section ".init.binary_info_header"
//  binary_info_header:

  .long 0xffffded3
  .long 0x10210142
  .long 0x000001ff
  .long 0x00000000
  .long 0xab123579

  .text
end;

end.

