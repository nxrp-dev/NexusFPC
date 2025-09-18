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

//type
//  TIRQn_Enum = (
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
//  );
type

  TINTERP_Registers = record
    accum : array[0..1] of longWord;
    base : array[0..2] of longWord;
    pop : array[0..2] of longWord;
    peek : array[0..2] of longWord;
    ctrl : array[0..1] of longWord;
    add_raw : array[0..1] of longWord;
    base01 : longWord;
  end;

  TSIO_Registers = record
    CPUID: longword;
    GPIO_IN: longword;
    GPIO_HI_IN: longword;
    Reservado1: longword;
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
    Reservado2: array[0..7] of longword;
    INTERP: array[0..1] of TINTERP_Registers;
    SPINLOCK: array[0..31] of longword;
    DOORBELL_OUT_SET: longword;
    DOORBELL_OUT_CLR: longword;
    DOORBELL_IN_SET: longword;
    DOORBELL_IN_CLR: longword;
    PERI_NONSEC: longword;
    Reservado3: array[0..3] of longword;
    RISCV_SOFTIRQ: longword;
    MTIME_CTRL: longword;
    Reservado4: array[0..1] of longword;
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
    TMDS_POP_DOUBLE_L2: longword;
  end;

  TPADSBANK0_Registers = record
    voltage_select : longWord;
    io : array[0..44] of longWord;
  end;

  TIOIRQCTRL_Registers = record
    inte : array[0..5] of longWord;
    intf : array[0..5] of longWord;
    ints : array[0..5] of longWord;
  end;

  TIOBANK0_Registers = record
    io : array[0..47] of record
      status : longWord;
      ctrl : longWord;
    end;
    irq_summary : array[0..11] of longword;
    intr: array[0..5] of longword;
    proc0_irq_ctrl : TIOIRQCTRL_Registers;
    proc1_irq_ctrl : TIOIRQCTRL_Registers;
    dormant_wake_irq_ctrl : TIOIRQCTRL_Registers;
  end;

  PCLOCK_Registers = ^TCLOCK_Registers;
  TCLOCK_Registers = record
    ctrl : longWord;
    &div : longWord;
    selected : longWord;
  end;

  PFC_Registers = ^TFC_Registers;
  TFC_Registers = record
    ref_khz : longWord;
    min_khz : longWord;
    max_khz : longWord;
    delay : longWord;
    interval : longWord;
    src : longWord;
    status : longWord;
    result : longWord;
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
      ctrl : longWord;
      status : longWord;
    end;
    fc0 : TFC_Registers;
    wake_en0 : longWord;
    wake_en1 : longWord;
    sleep_en0 : longWord;
    sleep_en1 : longWord;
    enabled0 : longWord;
    enabled1 : longWord;
    intr : longWord;
    inte : longWord;
    intf : longWord;
    ints : longWord;
  end;

  TCLOCKS_Registers_alt = record
    clk: array[0..9] of TCLOCK_Registers; // Array of clock configurations
    DFTCLK: record
      XOSC_CTRL: longword;
      ROSC_CTRL: longword;
      LPOSC_CTRL: longword;
    end;
    clk_sys_resus : record
      ctrl : longWord;
      status : longWord;
    end;
    fc0 : TFC_Registers;
    wake_en0 : longWord;
    wake_en1 : longWord;
    sleep_en0 : longWord;
    sleep_en1 : longWord;
    enabled0 : longWord;
    enabled1 : longWord;
    intr : longWord;
    inte : longWord;
    intf : longWord;
    ints : longWord;
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
(*
type
  TADC_Registers = record
    cs : longWord;
    result : longWord;
    fcs : longWord;
    fifo : longWord;
    &div : longWord;
    intr : longWord;
    inte : longWord;
    intf : longWord;
    ints : longWord;
  end;

  TBUSCTRL_Registers = record
    priority : longWord;
    priority_ack : longWord;
    perf : array[0..3] of record
      ctr : longWord;
      sel : longWord;
    end;
  end;
*)
(*
  TDMACHANNEL_Registers = record
    read_addr : longWord;
    write_addr : longWord;
    transfer_count : longWord;
    ctrl_trig : longWord;
    al1_ctrl : longWord;
    al1_read_addr : longWord;
    al1_write_addr : longWord;
    al1_transfer_count_trig : longWord;
    al2_ctrl : longWord;
    al2_transfer_count : longWord;
    al2_read_addr : longWord;
    al2_write_addr_trig : longWord;
    al3_ctrl : longWord;
    al3_write_addr : longWord;
    al3_transfer_count : longWord;
    al3_read_addr_trig : longWord;
  end;

  TDMA_Registers = record
    ch : array[0..11] of TDMACHANNEL_Registers;
    RESERVED0 : array[0..63] of longWord;
    intr : longWord;
    inte0 : longWord;
    intf0 : longWord;
    ints0 : longWord;
    RESERVED1 : longWord;
    inte1 : longWord;
    intf1 : longWord;
    ints1 : longWord;
    timer : array[0..1] of longWord;
    RESERVED2 : array[0..1] of longWord;
    multi_channel_trigger : longWord;
    sniff_ctrl : longWord;
    sniff_data : longWord;
    RESERVED3 : longWord;
    fifo_levels : longWord;
    abort : longWord;
  end;

  TDMADEBUG_Registers = record
    ch : array[0..11] of record
      ctrdeq : longWord;
      tcr : longWord;
      RESERVED0 : array[0..13] of longWord;
    end;
  end;

  TI2C_Registers = record
    con : longWord;
    tar : longWord;
    sar : longWord;
    RESERVED0 : longWord;
    data_cmd : longWord;
    ss_scl_hcnt : longWord;
    ss_scl_lcnt : longWord;
    fs_scl_hcnt : longWord;
    fs_scl_lcnt : longWord;
    RESERVED1 : array[0..1] of longWord;
    intr_stat : longWord;
    intr_mask : longWord;
    raw_intr_stat : longWord;
    rx_tl : longWord;
    tx_tl : longWord;
    clr_intr : longWord;
    clr_rx_under : longWord;
    clr_rx_over : longWord;
    clr_tx_over : longWord;
    clr_rd_req : longWord;
    clr_tx_abrt : longWord;
    clr_rx_done : longWord;
    clr_activity : longWord;
    clr_stop_det : longWord;
    clr_start_det : longWord;
    clr_gen_call : longWord;
    enable : longWord;
    status : longWord;
    txflr : longWord;
    rxflr : longWord;
    sda_hold : longWord;
    tx_abrt_source : longWord;
    slv_data_nack_only : longWord;
    dma_cr : longWord;
    dma_tdlr : longWord;
    dma_rdlr : longWord;
    sda_setup : longWord;
    ack_general_call : longWord;
    enable_status : longWord;
    fs_spklen : longWord;
    RESERVED2 : longWord;
    clr_restart_det : longWord;
    RESERVED3 : array[0..17] of longWord;
    comp_param_1 : longWord;
    comp_version : longWord;
    comp_type : longWord;
  end;

  TIOIRQCTRL_Registers = record
    inte : array[0..3] of longWord;
    intf : array[0..3] of longWord;
    ints : array[0..3] of longWord;
  end;

  TIOBANK0_Registers = record
    io : array[0..29] of record
      status : longWord;
      ctrl : longWord;
    end;
    intr : array[0..3] of longWord;
    proc0_irq_ctrl : TIOIRQCTRL_Registers;
    proc1_irq_ctrl : TIOIRQCTRL_Registers;
    dormant_wake_irq_ctrl : TIOIRQCTRL_Registers;
  end;

  TIOQSPI_Registers = record
    io : array[0..5] of record
      status : longWord;
      ctrl : longWord;
    end;
  end;

  TPADSQSPI_Registers = record
    voltage_select : longWord;
    io : array[0..5] of longWord;
  end;

  TPADSBANK0_Registers = record
    voltage_select : longWord;
    io : array[0..29] of longWord;
  end;

  TPIO_Registers = record
    ctrl : longWord;
    fstat : longWord;
    fdebug : longWord;
    flevel : longWord;
    txf : array[0..1] of longWord;
    rxf : array[0..1] of longWord;
    irq : longWord;
    irq_force : longWord;
    input_sync_bypass : longWord;
    dbg_padout : longWord;
    dbg_padoe : longWord;
    dbg_cfginfo : longWord;
    instr_mem : array[0..31] of longWord;
    sm : array[0..1] of record
      clkdiv : longWord;
      execctrl : longWord;
      shiftctrl : longWord;
      addr : longWord;
      instr : longWord;
      pinctrl : longWord;
    end;
    intr : longWord;
    inte0 : longWord;
    intf0 : longWord;
    ints0 : longWord;
    inte1 : longWord;
    intf1 : longWord;
    ints1 : longWord;
  end;
*)
  TPLL_Registers = record
    cs : longWord;
    pwr : longWord;
    fbdiv_int : longWord;
    prim : longWord;
    intr: longword;
    inte: longword;
    intf: longword;
    ints: longword;
  end;
(*
  TPSM_Registers = record
    frce_on : longWord;
    frce_off : longWord;
    wdsel : longWord;
    done : longWord;
  end;

  TPWMSLICE_Registers = record
    csr : longWord;
    &div : longWord;
    ctr : longWord;
    cc : longWord;
    top : longWord;
  end;

  TPWM_Registers = record
    slice : array[0..7] of TPWMSLICE_Registers;
    en : longWord;
    intr : longWord;
    inte : longWord;
    intf : longWord;
    ints : longWord;
  end;
*)
  TRESETS_Registers = record
    reset : longWord;
    wdsel : longWord;
    reset_done : longWord;
  end;
(*
  TROSC_Registers = record
    ctrl : longWord;
    freqa : longWord;
    freqb : longWord;
    dormant : longWord;
    &div : longWord;
    phase : longWord;
    status : longWord;
    randombit : longWord;
    count : longWord;
    dftx : longWord;
  end;

  TRTC_Registers = record
    clkdiv_m1 : longWord;
    setup_0 : longWord;
    setup_1 : longWord;
    ctrl : longWord;
    irq_setup_0 : longWord;
    irq_setup_1 : longWord;
    rtc_1 : longWord;
    rtc_0 : longWord;
    intr : longWord;
    inte : longWord;
    intf : longWord;
    ints : longWord;
  end;

  TINTERP_Registers = record
    accum : array[0..1] of longWord;
    base : array[0..2] of longWord;
    pop : array[0..2] of longWord;
    peek : array[0..2] of longWord;
    ctrl : array[0..1] of longWord;
    add_raw : array[0..1] of longWord;
    base01 : longWord;
  end;

  TSPI_Registers = record
    cr0 : longWord;
    cr1 : longWord;
    dr : longWord;
    sr : longWord;
    cpsr : longWord;
    imsc : longWord;
    ris : longWord;
    mis : longWord;
    icr : longWord;
    dmacr : longWord;
  end;

  TSSI_Registers = record
    ctrlr0 : longWord;
    ctrlr1 : longWord;
    ssienr : longWord;
    mwcr : longWord;
    ser : longWord;
    baudr : longWord;
    txftlr : longWord;
    rxftlr : longWord;
    txflr : longWord;
    rxflr : longWord;
    sr : longWord;
    imr : longWord;
    isr : longWord;
    risr : longWord;
    txoicr : longWord;
    rxoicr : longWord;
    rxuicr : longWord;
    msticr : longWord;
    icr : longWord;
    dmacr : longWord;
    dmatdlr : longWord;
    dmardlr : longWord;
    idr : longWord;
    ssi_version_id : longWord;
    dr0 : longWord;
    RESERVED0 : array[0..34] of longWord;
    rx_sample_dly : longWord;
    spi_ctrlr0 : longWord;
    txd_drive_edge : longWord;
  end;

  TSYSCFG_Registers = record
    proc0_nmi_mask : longWord;
    proc1_nmi_mask : longWord;
    proc_config : longWord;
    proc_in_sync_bypass : longWord;
    proc_in_sync_bypass_hi : longWord;
    dbgforce : longWord;
    mempowerdown : longWord;
  end;

  TSYSINFO_Registers = record
    chip_id : longWord;
    platform : longWord;
    reserved0 : array[0..$3F-$08] of longWord;
    gitref_rp2040 : longWord;
  end;
*)

  TTIMER_Registers = record
    timehw : longWord;
    timelw : longWord;
    timehr : longWord;
    timelr : longWord;
    alarm : array[0..3] of longWord;
    armed : longWord;
    timerawh : longWord;
    timerawl : longWord;
    dbgpause : longWord;
    pause : longWord;
    locked: longword;
    source: longword;
    intr : longWord;
    inte : longWord;
    intf : longWord;
    ints : longWord;
  end;
(*
  TUART_Registers = record
    dr : longWord;
    rsr : longWord;
    RESERVED0 : array[0..3] of longWord;
    fr : longWord;
    RESERVED1 : longWord;
    ilpr : longWord;
    ibrd : longWord;
    fbrd : longWord;
    lcr_h : longWord;
    cr : longWord;
    ifls : longWord;
    imsc : longWord;
    ris : longWord;
    mis : longWord;
    icr : longWord;
    dmacr : longWord;
  end;

  TUSBDEVICEDPRAM = record
    setup_packet : array[0..7] of byte;
    ep_ctrl : array[0..14] of record
      &in : longWord;
      &out : longWord;
    end;
    ep_buf_ctrl : array[0..15] of record
      &in : longWord;
      &out : longWord;
    end;
    ep0_buf_a : array[0..63] of byte;
    ep0_buf_b : array[0..63] of byte;
    epx_data : array[0..(4096-$180)-1] of byte;
  end;

  TUSBHOSTDPRAM = record
    setup_packet : array[0..7] of byte;
    int_ep_ctrl : array[0..14] of record
      ctrl : longWord;
      spare : longWord;
    end;
    epx_buf_ctrl : longWord;
    _spare0 : longWord;
    int_ep_buffer_ctrl : array[0..14] of record
      ctrl : longWord;
      spare : longWord;
    end;
    epx_ctrl : longWord;
    _spare1 : array[0..123] of byte;
    epx_data : array[0..(4096-$180)-1] of byte;
  end;

  TUSB_Registers = record
    dev_addr_ctrl : longWord;
    int_ep_addr_ctrl : array[1..15] of longWord;
    main_ctrl : longWord;
    sof_wr : longWord;
    sof_rd : longWord;
    sie_ctrl : longWord;
    sie_status : longWord;
    int_ep_ctrl : longWord;
    buf_status : longWord;
    buf_cpu_should_handle : longWord;
    abort : longWord;
    abort_done : longWord;
    ep_stall_arm : longWord;
    nak_poll : longWord;
    ep_nak_stall_status : longWord;
    muxing : longWord;
    pwr : longWord;
    phy_direct : longWord;
    phy_direct_override : longWord;
    phy_trim : longWord;
    linestate_tuning : longWord;
    intr : longWord;
    inte : longWord;
    intf : longWord;
    ints : longWord;
  end;

  TVREGANDCHIPRESET_Registers = record
    vreg : longWord;
    bod : longWord;
    chip_reset : longWord;
  end;
*)
  TWATCHDOG_Registers = record
    ctrl : longWord;
    load : longWord;
    reason : longWord;
    scratch : array[0..7] of longWord;
//    tick : longWord;
  end;
(*
  TXIPCTRL_Registers = record
    ctrl : longWord;
    flush : longWord;
    stat : longWord;
    ctr_hit : longWord;
    ctr_acc : longWord;
    stream_addr : longWord;
    stream_ctr : longWord;
    stream_fifo : longWord;
  end;
*)
  TXOSC_Registers = record
    ctrl : longWord;
    status : longWord;
    dormant : longWord;
    startup : longWord;
//    RESERVED0 : array[0..2] of longWord;
    count : longWord;
  end;
(*
  TMPU_Registers = record
    _type : longWord;
    ctrl : longWord;
    rnr : longWord;
    rbar : longWord;
    rasr : longWord;
  end;
*)
  TSYSTICK_Registers = record
    csr : longWord;
    rvr : longWord;
    cvr : longWord;
    calib : longWord;
  end;
(*
  TSCB_Reqisters = record
    cpuid : longWord;
    icsr : longWord;
    vtor : longWord;
    aircr : longWord;
    scr : longWord;
  end;
*)


var
  SIO : TSIO_Registers absolute SIO_BASE;
//  PPB: array[0..$367] of longword absolute BBP_BASE;
  TICK : TSYSTICK_Registers absolute (PPB_BASE + SYST_CSR);
  PADSBANK0 : TPADSBANK0_Registers absolute PADS_BANK0_BASE;
  IOBANK0 : TIOBANK0_Registers absolute IO_BANK0_BASE;
  RESETS : TRESETS_Registers absolute RESETS_BASE;
  PLLSYS : TPLL_Registers absolute PLL_SYS_BASE;
  PLLUSB : TPLL_Registers absolute PLL_USB_BASE;
  CLOCKS : TCLOCKS_Registers absolute CLOCKS_BASE;
  _CLOCKS : TCLOCKS_Registers_ALT absolute CLOCKS_BASE;
  TIMER0 : TTIMER_Registers absolute TIMER0_BASE;
  TIMER1 : TTIMER_Registers absolute TIMER1_BASE;
  XOSC : TXOSC_Registers absolute XOSC_BASE;
  WATCHDOG : TWATCHDOG_Registers absolute WATCHDOG_BASE;
  TICKS: TTICKS_Registers absolute TICKS_BASE;
(*
  SysInfo : TSysInfo_Registers absolute SYSINFO_BASE;
  SysCfg : TSYSCFG_REGISTERS absolute SYSCFG_BASE;
  PSM : TPSM_Registers absolute PSM_BASE;
//  IOBANK0 : TIOBANK0_Registers absolute IO_BANK0_BASE;
  IOQSPI : TIOQSPI_Registers absolute IO_QSPI_BASE;
//  PADSBANK0 : TPADSBANK0_Registers absolute PADS_BANK0_BASE;
  PADSQSPI : TPADSQSPI_Registers absolute PADS_QSPI_BASE;
  BUSCTRL : TBUSCTRL_Registers absolute BUSCTRL_BASE;
  UART0 : TUART_Registers absolute UART0_BASE;
  UART1 : TUART_Registers absolute UART1_BASE;
  SPI0 : TSPI_Registers absolute SPI0_BASE;
  SPI1 : TSPI_Registers absolute SPI1_BASE;
  I2C0 : TI2C_Registers absolute I2C0_BASE;
  I2C1 : TI2C_Registers absolute I2C1_BASE;
  ADC : TADC_Registers absolute ADC_BASE;
  PWM : TPWM_Registers absolute PWM_BASE;
  RTC : TRTC_Registers absolute RTC_BASE;
  ROSC : TROSC_Registers absolute ROSC_BASE;
  VREGANDCHIPRESET : TVREGANDCHIPRESET_Registers absolute VREG_AND_CHIP_RESET_BASE;
  DMA : TDMA_Registers absolute DMA_BASE;
  //USBCTRL_BASE = $50100000
  //USBCTRL_DPRAM_BASE = $50100000
  USB : TUSB_Registers absolute USBCTRL_REGS_BASE;
  PIO0 : TPIO_Registers absolute PIO0_BASE;
  PIO1 : TPIO_Registers absolute PIO1_BASE;
  //XIP_AUX_BASE = $50400000
//  SIO : TSIO_Registers absolute SIO_BASE;

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

