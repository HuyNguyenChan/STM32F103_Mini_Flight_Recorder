/* STM32F103C8T6 mini flight recorder.
 * Bare-metal register firmware, no HAL/CMSIS.
 */

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef signed short   int16_t;
typedef signed int     int32_t;

/* ===================== Memory map ===================== */
#define PERIPH_BASE       0x40000000UL
#define APB1_BASE         PERIPH_BASE
#define APB2_BASE         (PERIPH_BASE + 0x00010000UL)
#define AHB_BASE          (PERIPH_BASE + 0x00020000UL)

#define TIM2_BASE         (APB1_BASE + 0x00000000UL)
#define I2C1_BASE         (APB1_BASE + 0x00005400UL)
#define GPIOA_BASE        (APB2_BASE + 0x00000800UL)
#define GPIOB_BASE        (APB2_BASE + 0x00000C00UL)
#define SPI1_BASE         (APB2_BASE + 0x00003000UL)
#define USART1_BASE       (APB2_BASE + 0x00003800UL)
#define RCC_BASE          (AHB_BASE  + 0x00001000UL)
#define FLASH_BASE        0x40022000UL
#define SYSTICK_BASE      0xE000E010UL
#define NVIC_ISER0_ADDR   0xE000E100UL

/* ===================== Register structs ===================== */
typedef struct {
    volatile uint32_t ACR, KEYR, OPTKEYR, SR, CR, AR, RESERVED, OBR, WRPR;
} FLASH_TypeDef;

typedef struct {
    volatile uint32_t CR, CFGR, CIR, APB2RSTR, APB1RSTR;
    volatile uint32_t AHBENR, APB2ENR, APB1ENR, BDCR, CSR;
} RCC_TypeDef;

typedef struct {
    volatile uint32_t CRL, CRH, IDR, ODR, BSRR, BRR, LCKR;
} GPIO_TypeDef;

typedef struct {
    volatile uint32_t SR, DR, BRR, CR1, CR2, CR3, GTPR;
} USART_TypeDef;

typedef struct {
    volatile uint32_t CR1, CR2, OAR1, OAR2, DR, SR1, SR2, CCR, TRISE;
} I2C_TypeDef;

typedef struct {
    volatile uint32_t CR1, CR2, SR, DR, CRCPR, RXCRCR, TXCRCR, I2SCFGR, I2SPR;
} SPI_TypeDef;

typedef struct {
    volatile uint32_t CR1, CR2, SMCR, DIER, SR, EGR;
    volatile uint32_t CCMR1, CCMR2, CCER, CNT, PSC, ARR, RESERVED1;
    volatile uint32_t CCR1, CCR2, CCR3, CCR4, RESERVED2, DCR, DMAR;
} TIM_TypeDef;

typedef struct {
    volatile uint32_t CTRL, LOAD, VAL, CALIB;
} SysTick_TypeDef;

typedef struct {
    int16_t ax, ay, az, gx, gy, gz;
} MpuSample_TypeDef;

#define FLASH       ((FLASH_TypeDef   *)FLASH_BASE)
#define RCC         ((RCC_TypeDef     *)RCC_BASE)
#define GPIOA       ((GPIO_TypeDef    *)GPIOA_BASE)
#define GPIOB       ((GPIO_TypeDef    *)GPIOB_BASE)
#define USART1      ((USART_TypeDef   *)USART1_BASE)
#define I2C1        ((I2C_TypeDef     *)I2C1_BASE)
#define SPI1        ((SPI_TypeDef     *)SPI1_BASE)
#define TIM2        ((TIM_TypeDef     *)TIM2_BASE)
#define SYSTICK     ((SysTick_TypeDef *)SYSTICK_BASE)
#define NVIC_ISER0  (*(volatile uint32_t *)NVIC_ISER0_ADDR)
#define SPI1_DR8    (*(volatile uint8_t *)&SPI1->DR)

/* ===================== Bit masks ===================== */
#define RCC_CR_HSION          (1U << 0)
#define RCC_CR_HSIRDY         (1U << 1)
#define RCC_CR_HSEON          (1U << 16)
#define RCC_CR_HSERDY         (1U << 17)
#define RCC_CR_PLLON          (1U << 24)
#define RCC_CR_PLLRDY         (1U << 25)

#define RCC_CFGR_SW           (3U << 0)
#define RCC_CFGR_SW_HSI       (0U << 0)
#define RCC_CFGR_SW_PLL       (2U << 0)
#define RCC_CFGR_SWS          (3U << 2)
#define RCC_CFGR_SWS_HSI      (0U << 2)
#define RCC_CFGR_SWS_PLL      (2U << 2)
#define RCC_CFGR_PPRE1_DIV2   (4U << 8)
#define RCC_CFGR_PLLSRC_HSE   (1U << 16)
#define RCC_CFGR_PLLMULL9     (7U << 18)

#define RCC_APB2ENR_AFIOEN    (1U << 0)
#define RCC_APB2ENR_IOPAEN    (1U << 2)
#define RCC_APB2ENR_IOPBEN    (1U << 3)
#define RCC_APB2ENR_SPI1EN    (1U << 12)
#define RCC_APB2ENR_USART1EN  (1U << 14)

#define RCC_APB1ENR_TIM2EN    (1U << 0)
#define RCC_APB1ENR_I2C1EN    (1U << 21)
#define RCC_APB1RSTR_I2C1RST  (1U << 21)

#define FLASH_ACR_LATENCY_2   (2U << 0)
#define FLASH_ACR_PRFTBE      (1U << 4)

#define USART_SR_TXE          (1U << 7)
#define USART_CR1_RE          (1U << 2)
#define USART_CR1_TE          (1U << 3)
#define USART_CR1_UE          (1U << 13)

#define I2C_CR1_PE            (1U << 0)
#define I2C_CR1_START         (1U << 8)
#define I2C_CR1_STOP          (1U << 9)
#define I2C_CR1_ACK           (1U << 10)
#define I2C_CR1_POS           (1U << 11)

#define I2C_SR1_SB            (1U << 0)
#define I2C_SR1_ADDR          (1U << 1)
#define I2C_SR1_BTF           (1U << 2)
#define I2C_SR1_RXNE          (1U << 6)
#define I2C_SR1_TXE           (1U << 7)

#define I2C_SR2_MSL           (1U << 0)
#define I2C_SR2_BUSY          (1U << 1)
#define I2C_SR2_TRA           (1U << 2)
#define I2C_SR2_MBB_TX        (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA)
#define I2C_SR2_MBB_RX        (I2C_SR2_MSL | I2C_SR2_BUSY)

#define SPI_CR1_MSTR          (1U << 2)
#define SPI_CR1_BR_DIV64      (5U << 3)
#define SPI_CR1_SPE           (1U << 6)
#define SPI_CR1_SSI           (1U << 8)
#define SPI_CR1_SSM           (1U << 9)

#define SPI_SR_RXNE           (1U << 0)
#define SPI_SR_TXE            (1U << 1)
#define SPI_SR_BSY            (1U << 7)

#define TIM_CR1_CEN           (1U << 0)
#define TIM_CR1_ARPE          (1U << 7)
#define TIM_DIER_UIE          (1U << 0)
#define TIM_SR_UIF            (1U << 0)
#define TIM_EGR_UG            (1U << 0)
#define TIM2_IRQ_NUMBER       28U

#define SYSTICK_CTRL_ENABLE     (1U << 0)
#define SYSTICK_CTRL_CLKSOURCE  (1U << 2)
#define SYSTICK_CTRL_COUNTFLAG  (1U << 16)

/* ===================== Configuration ===================== */
#define GPIO_INPUT_FLOATING   0x4U
#define GPIO_INPUT_PULL       0x8U
#define GPIO_OUTPUT_PP_2MHZ   0x2U
#define GPIO_OUTPUT_PP_50MHZ  0x3U
#define GPIO_AF_PP_50MHZ      0xBU
#define GPIO_AF_OD_50MHZ      0xFU

#define W25_CMD_WRITE_ENABLE   0x06U
#define W25_CMD_READ_STATUS_1  0x05U
#define W25_CMD_WRITE_STATUS_1 0x01U
#define W25_CMD_PAGE_PROGRAM   0x02U
#define W25_CMD_READ_DATA      0x03U
#define W25_CMD_CHIP_ERASE     0xC7U
#define W25_STATUS_BUSY        (1U << 0)
#define W25_PAGE_SIZE          256U
#define W25Q64_SIZE_BYTES      0x00800000UL

#define MPU6050_ADDR             0x68U
#define MPU6050_REG_PWR_MGMT_1   0x6BU
#define MPU6050_REG_ACCEL_XOUT_H 0x3BU

#define BUTTON_RECORD_PIN   0U
#define BUTTON_DUMP_PIN     1U
#define SPI_CS_PIN          4U
#define SPI_SCK_PIN         5U
#define SPI_MISO_PIN        6U
#define SPI_MOSI_PIN        7U
#define I2C1_SCL_PIN        6U
#define I2C1_SDA_PIN        7U
#define USART1_TX_PIN       9U
#define USART1_RX_PIN       10U
#define LED_GREEN_PIN       0U

#define SAMPLE_INTERVAL_TICKS 100U
#define BUTTON_HOLD_TICKS     300UL
#define SAMPLE_TEXT_MAX       96U

static volatile uint8_t  sample_flag = 0U;
static volatile uint8_t  sample_tick_divider = 0U;
static volatile uint32_t system_ticks_10ms = 0UL;

static uint8_t  recording = 0U;
static uint32_t flash_addr = 0UL;
static uint32_t sample_count = 0UL;
static char     sample_text[SAMPLE_TEXT_MAX];
static uint16_t sample_text_len = 0U;

void SystemInit(void);
void TIM2_IRQHandler(void);

void SystemInit(void) { }

/* ===================== GPIO / delay ===================== */
static void GPIO_ConfigPin(GPIO_TypeDef *port, uint8_t pin, uint8_t config)
{
    volatile uint32_t *cr = (pin < 8U) ? &port->CRL : &port->CRH;
    uint32_t shift = ((uint32_t)pin & 7UL) * 4UL;
    *cr = (*cr & ~(0xFUL << shift)) | ((uint32_t)config << shift);
}

static uint8_t GPIO_ReadPin(GPIO_TypeDef *port, uint8_t pin)
{
    return ((port->IDR & (1UL << pin)) != 0UL) ? 1U : 0U;
}

static void GPIO_WritePin(GPIO_TypeDef *port, uint8_t pin, uint8_t level)
{
    port->BSRR = (level != 0U) ? (1UL << pin) : (1UL << (pin + 16U));
}

static uint8_t Button_IsPressed(uint8_t pin)
{
    return (GPIO_ReadPin(GPIOA, pin) == 0U) ? 1U : 0U;
}

static void Delay_ms(uint32_t ms)
{
    while (ms-- != 0U)
    {
        SYSTICK->LOAD = 72000U - 1U;
        SYSTICK->VAL  = 0U;
        SYSTICK->CTRL = SYSTICK_CTRL_CLKSOURCE | SYSTICK_CTRL_ENABLE;
        while ((SYSTICK->CTRL & SYSTICK_CTRL_COUNTFLAG) == 0U) { }
        SYSTICK->CTRL = 0U;
    }
}

/* ===================== Init ===================== */
static void Clock_Init_72MHz_HSE8(void)
{
    RCC->CR |= RCC_CR_HSION;
    while ((RCC->CR & RCC_CR_HSIRDY) == 0U) { }

    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_HSI;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI) { }

    RCC->CR &= ~RCC_CR_PLLON;
    while ((RCC->CR & RCC_CR_PLLRDY) != 0U) { }

    RCC->CR |= RCC_CR_HSEON;
    while ((RCC->CR & RCC_CR_HSERDY) == 0U) { }

    FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY_2;
    RCC->CFGR = RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9;

    RCC->CR |= RCC_CR_PLLON;
    while ((RCC->CR & RCC_CR_PLLRDY) == 0U) { }

    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) { }
}

static void GPIO_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;

    GPIO_ConfigPin(GPIOA, BUTTON_RECORD_PIN, GPIO_INPUT_PULL);
    GPIO_ConfigPin(GPIOA, BUTTON_DUMP_PIN,   GPIO_INPUT_PULL);
    GPIOA->ODR |= (1UL << BUTTON_RECORD_PIN) | (1UL << BUTTON_DUMP_PIN);

    GPIO_ConfigPin(GPIOB, LED_GREEN_PIN, GPIO_OUTPUT_PP_2MHZ);
    GPIO_WritePin(GPIOB, LED_GREEN_PIN, 0U);
}

static void USART1_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN;
    GPIO_ConfigPin(GPIOA, USART1_TX_PIN, GPIO_AF_PP_50MHZ);
    GPIO_ConfigPin(GPIOA, USART1_RX_PIN, GPIO_INPUT_FLOATING);
    USART1->BRR = 0x1D4CU;  /* 9600 baud @ 72 MHz */
    USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

static void I2C1_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;
    GPIO_ConfigPin(GPIOB, I2C1_SCL_PIN, GPIO_AF_OD_50MHZ);
    GPIO_ConfigPin(GPIOB, I2C1_SDA_PIN, GPIO_AF_OD_50MHZ);

    RCC->APB1ENR  |=  RCC_APB1ENR_I2C1EN;
    RCC->APB1RSTR |=  RCC_APB1RSTR_I2C1RST;
    RCC->APB1RSTR &= ~RCC_APB1RSTR_I2C1RST;

    I2C1->CR1 &= ~I2C_CR1_PE;
    I2C1->CR2   = 36U;
    I2C1->CCR   = 180U;
    I2C1->TRISE = 37U;
    I2C1->CR1  |= I2C_CR1_PE;
}

static void SPI1_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_SPI1EN;

    GPIO_ConfigPin(GPIOA, SPI_CS_PIN,   GPIO_OUTPUT_PP_50MHZ);
    GPIO_ConfigPin(GPIOA, SPI_SCK_PIN,  GPIO_AF_PP_50MHZ);
    GPIO_ConfigPin(GPIOA, SPI_MISO_PIN, GPIO_INPUT_FLOATING);
    GPIO_ConfigPin(GPIOA, SPI_MOSI_PIN, GPIO_AF_PP_50MHZ);

    GPIO_WritePin(GPIOA, SPI_CS_PIN, 1U);
    /* Toc do cham hon de on dinh khi cam breadboard/day dai. */
    SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_BR_DIV64 | SPI_CR1_SSM | SPI_CR1_SSI;
    SPI1->CR2 = 0U;
    SPI1->CR1 |= SPI_CR1_SPE;
}

static void TIM2_Init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    /* TIM2 tao interrupt moi 10 ms. ISR chi tang tick va set co lay mau. */
    TIM2->CR1 &= ~TIM_CR1_CEN;
    TIM2->PSC = 7199U;  /* 72 MHz / 7200 = 10 kHz */
    TIM2->ARR = 99U;    /* 10 kHz / 100 = 100 Hz = 10 ms */
    TIM2->EGR = TIM_EGR_UG;
    TIM2->SR &= ~TIM_SR_UIF;
    TIM2->DIER |= TIM_DIER_UIE;
    NVIC_ISER0 |= (1U << TIM2_IRQ_NUMBER);
    TIM2->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;
}

void TIM2_IRQHandler(void)
{
    if ((TIM2->SR & TIM_SR_UIF) != 0U)
    {
        TIM2->SR &= ~TIM_SR_UIF;
        system_ticks_10ms++;

        /* 100 lan 10 ms = 1 giay, bao main doc MPU6050. */
        if (++sample_tick_divider >= SAMPLE_INTERVAL_TICKS)
        {
            sample_tick_divider = 0U;
            sample_flag = 1U;
        }
    }
}

/* ===================== USART ===================== */
static void USART1_SendChar(char c)
{
    while ((USART1->SR & USART_SR_TXE) == 0U) { }
    USART1->DR = (uint8_t)c;
}

static void USART1_SendString(const char *s)
{
    while (*s != '\0') { USART1_SendChar(*s++); }
}

/* ===================== I2C + MPU6050 ===================== */
static void I2C_WaitBusFree(void) { while ((I2C1->SR2 & I2C_SR2_BUSY) != 0U) { } }
static void I2C_WaitSR1Set(uint32_t flag) { while ((I2C1->SR1 & flag) == 0U) { } }
static void I2C_WaitSR2Value(uint32_t mask, uint32_t value) { while ((I2C1->SR2 & mask) != value) { } }

static void I2C_ClearADDR(void)
{
    volatile uint32_t tmp;
    tmp = I2C1->SR1;
    tmp = I2C1->SR2;
    (void)tmp;
}

static void I2C_StartWriteReg(uint8_t addr, uint8_t reg)
{
    I2C1->CR1 |= I2C_CR1_START;
    I2C_WaitSR1Set(I2C_SR1_SB);
    I2C1->DR = (uint8_t)((uint32_t)addr << 1);
    I2C_WaitSR1Set(I2C_SR1_ADDR);
    I2C_ClearADDR();
    I2C_WaitSR2Value(I2C_SR2_MBB_TX, I2C_SR2_MBB_TX);
    I2C_WaitSR1Set(I2C_SR1_TXE);
    I2C1->DR = reg;
    I2C_WaitSR1Set(I2C_SR1_BTF);
}

static void I2C_WriteByte(uint8_t addr, uint8_t reg, uint8_t data)
{
    I2C_WaitBusFree();
    I2C_StartWriteReg(addr, reg);
    I2C1->DR = data;
    I2C_WaitSR1Set(I2C_SR1_BTF);
    I2C1->CR1 |= I2C_CR1_STOP;
}

static void I2C_ReadBytes(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if ((buf == (uint8_t *)0) || (len < 3U)) { return; }

    /* Ghi dia chi register truoc, sau do repeated START de chuyen sang doc. */
    I2C_WaitBusFree();
    I2C1->CR1 |=  I2C_CR1_ACK;
    I2C1->CR1 &= ~I2C_CR1_POS;
    I2C_StartWriteReg(addr, reg);

    I2C1->CR1 |= I2C_CR1_START;
    I2C_WaitSR1Set(I2C_SR1_SB);
    I2C1->DR = (uint8_t)(((uint32_t)addr << 1) | 1UL);
    I2C_WaitSR1Set(I2C_SR1_ADDR);
    I2C_ClearADDR();
    I2C_WaitSR2Value(I2C_SR2_MBB_TX, I2C_SR2_MBB_RX);

    /* Doc cac byte dau binh thuong khi van gui ACK. */
    while (len > 3U)
    {
        I2C_WaitSR1Set(I2C_SR1_RXNE);
        *buf++ = (uint8_t)I2C1->DR;
        len--;
    }

    /* Ba byte cuoi: tat ACK va tao STOP dung thu tu STM32F1 yeu cau. */
    I2C_WaitSR1Set(I2C_SR1_BTF);
    I2C1->CR1 &= ~I2C_CR1_ACK;
    *buf++ = (uint8_t)I2C1->DR;
    I2C_WaitSR1Set(I2C_SR1_BTF);
    I2C1->CR1 |= I2C_CR1_STOP;
    *buf++ = (uint8_t)I2C1->DR;
    *buf   = (uint8_t)I2C1->DR;
    I2C1->CR1 |= I2C_CR1_ACK;
}

static void MPU6050_Init(void)
{
    I2C_WriteByte(MPU6050_ADDR, MPU6050_REG_PWR_MGMT_1, 0x00U);
    Delay_ms(100U);
}

static void MPU6050_ReadSample(MpuSample_TypeDef *sample)
{
    uint8_t raw[14];

    I2C_ReadBytes(MPU6050_ADDR, MPU6050_REG_ACCEL_XOUT_H, raw, 14U);
    sample->ax = (int16_t)(((uint16_t)raw[0]  << 8) | raw[1]);
    sample->ay = (int16_t)(((uint16_t)raw[2]  << 8) | raw[3]);
    sample->az = (int16_t)(((uint16_t)raw[4]  << 8) | raw[5]);
    sample->gx = (int16_t)(((uint16_t)raw[8]  << 8) | raw[9]);
    sample->gy = (int16_t)(((uint16_t)raw[10] << 8) | raw[11]);
    sample->gz = (int16_t)(((uint16_t)raw[12] << 8) | raw[13]);
}

/* ===================== SPI + W25Q64 ===================== */
static uint8_t SPI_Transfer(uint8_t data)
{
    while ((SPI1->SR & SPI_SR_TXE) == 0U) { }
    SPI1_DR8 = data;
    while ((SPI1->SR & SPI_SR_RXNE) == 0U) { }
    return SPI1_DR8;
}

static void SPI1_CS_Low(void) { GPIO_WritePin(GPIOA, SPI_CS_PIN, 0U); }

static void SPI1_CS_High(void)
{
    while ((SPI1->SR & SPI_SR_BSY) != 0U) { }
    GPIO_WritePin(GPIOA, SPI_CS_PIN, 1U);
}

static void W25_CmdOnly(uint8_t cmd)
{
    SPI1_CS_Low();
    SPI_Transfer(cmd);
    SPI1_CS_High();
}

static uint8_t W25_ReadStatus1(void)
{
    uint8_t status;

    SPI1_CS_Low();
    SPI_Transfer(W25_CMD_READ_STATUS_1);
    status = SPI_Transfer(0xFFU);
    SPI1_CS_High();
    return status;
}

static void W25_WaitBusy(void)
{
    while ((W25_ReadStatus1() & W25_STATUS_BUSY) != 0U) { }
}

static void W25_WriteEnable(void)
{
    W25_CmdOnly(W25_CMD_WRITE_ENABLE);
}

static void W25_ClearProtection(void)
{
    W25_WaitBusy();
    W25_WriteEnable();

    SPI1_CS_Low();
    SPI_Transfer(W25_CMD_WRITE_STATUS_1);
    SPI_Transfer(0x00U);
    SPI1_CS_High();

    W25_WaitBusy();
}

static void W25_SendAddress24(uint32_t addr)
{
    SPI_Transfer((uint8_t)(addr >> 16));
    SPI_Transfer((uint8_t)(addr >> 8));
    SPI_Transfer((uint8_t)addr);
}

static void W25_PageProgram(uint32_t addr, const uint8_t *data, uint16_t len)
{
    uint16_t i;

    if ((data == (const uint8_t *)0) || (len == 0U)) { return; }
    if (len > W25_PAGE_SIZE) { len = W25_PAGE_SIZE; }

    W25_WaitBusy();
    W25_WriteEnable();

    SPI1_CS_Low();
    SPI_Transfer(W25_CMD_PAGE_PROGRAM);
    W25_SendAddress24(addr);
    for (i = 0U; i < len; i++) { SPI_Transfer(data[i]); }
    SPI1_CS_High();

    W25_WaitBusy();
}

static void W25_ReadData(uint32_t addr, uint8_t *buf, uint16_t len)
{
    uint16_t i;

    if ((buf == (uint8_t *)0) || (len == 0U)) { return; }
    W25_WaitBusy();

    SPI1_CS_Low();
    SPI_Transfer(W25_CMD_READ_DATA);
    W25_SendAddress24(addr);
    for (i = 0U; i < len; i++) { buf[i] = SPI_Transfer(0xFFU); }
    SPI1_CS_High();
}

static void W25_ChipErase(void)
{
    W25_WaitBusy();
    W25_WriteEnable();
    W25_CmdOnly(W25_CMD_CHIP_ERASE);
    W25_WaitBusy();
}

/* ===================== Text + recorder ===================== */
static void Text_Clear(void)
{
    sample_text_len = 0U;
    sample_text[0] = '\0';
}

static void Text_PutChar(char c)
{
    if (sample_text_len < (SAMPLE_TEXT_MAX - 1U))
    {
        sample_text[sample_text_len++] = c;
        sample_text[sample_text_len] = '\0';
    }
}

static void Text_PutString(const char *s)
{
    while (*s != '\0') { Text_PutChar(*s++); }
}

static void Text_PutUInt32(uint32_t value)
{
    char digits[10];
    uint32_t idx = 0U;

    do {
        digits[idx++] = (char)('0' + (value % 10UL));
        value /= 10UL;
    } while (value != 0U);

    while (idx != 0U) { Text_PutChar(digits[--idx]); }
}

static void Text_PutInt32(int32_t value)
{
    if (value < 0)
    {
        Text_PutChar('-');
        value = -value;
    }
    Text_PutUInt32((uint32_t)value);
}

static void Text_BuildSample(const MpuSample_TypeDef *s)
{
    Text_Clear();
    Text_PutString("AX:");
    Text_PutInt32(s->ax);
    Text_PutString(" AY:");
    Text_PutInt32(s->ay);
    Text_PutString(" AZ:");
    Text_PutInt32(s->az);
    Text_PutString(" GX:");
    Text_PutInt32(s->gx);
    Text_PutString(" GY:");
    Text_PutInt32(s->gy);
    Text_PutString(" GZ:");
    Text_PutInt32(s->gz);
    Text_PutString("\r\n");
}

static void Recorder_Stop(void)
{
    recording = 0U;
    sample_flag = 0U;
    sample_tick_divider = 0U;
    GPIO_WritePin(GPIOB, LED_GREEN_PIN, 0U);
}

static void Recorder_WriteLog(const char *data, uint16_t len)
{
    const uint8_t *p = (const uint8_t *)data;
    uint16_t chunk, page_space;

    /* Het flash thi dung ghi, khong ghi tran ra ngoai W25Q64. */
    if ((flash_addr + (uint32_t)len) > W25Q64_SIZE_BYTES)
    {
        Recorder_Stop();
        USART1_SendString("FLASH FULL\r\n");
        return;
    }

    /* W25Q64 khong cho Page Program vuot bien 256 byte cua mot page. */
    while (len != 0U)
    {
        page_space = (uint16_t)(W25_PAGE_SIZE - (uint16_t)(flash_addr & (W25_PAGE_SIZE - 1U)));
        chunk = (len < page_space) ? len : page_space;

        W25_PageProgram(flash_addr, p, chunk);
        flash_addr += (uint32_t)chunk;
        p += chunk;
        len -= chunk;
    }
}

static void Recorder_DumpText(void)
{
    uint8_t read_buf[64];
    uint16_t chunk, i;
    uint32_t addr = 0UL;
    uint32_t remaining = flash_addr;

    Recorder_Stop();
    USART1_SendString("DUMP START\r\n");

    while (remaining != 0UL)
    {
        chunk = (remaining > (uint32_t)sizeof(read_buf))
                ? (uint16_t)sizeof(read_buf)
                : (uint16_t)remaining;

        W25_ReadData(addr, read_buf, chunk);
        for (i = 0U; i < chunk; i++) { USART1_SendChar((char)read_buf[i]); }

        addr += (uint32_t)chunk;
        remaining -= (uint32_t)chunk;
    }

    USART1_SendString("DUMP END BYTES:");
    Text_Clear();
    Text_PutUInt32(flash_addr);
    USART1_SendString(sample_text);
    USART1_SendString(" SAMPLES:");
    Text_Clear();
    Text_PutUInt32(sample_count);
    USART1_SendString(sample_text);
    USART1_SendString("\r\n");
}

static void Recorder_EraseAll(void)
{
    Recorder_Stop();
    USART1_SendString("ERASE START\r\n");
    W25_ClearProtection();
    W25_ChipErase();
    flash_addr = 0UL;
    sample_count = 0UL;
    USART1_SendString("ERASE DONE\r\n");
}

/* ===================== Buttons ===================== */
static void Buttons_Task(void)
{
    uint32_t press_tick;
    uint8_t erased;

    if (Button_IsPressed(BUTTON_RECORD_PIN) != 0U)
    {
        Delay_ms(30U);
        if (Button_IsPressed(BUTTON_RECORD_PIN) != 0U)
        {
            recording = (recording == 0U) ? 1U : 0U;
            sample_flag = 0U;
            sample_tick_divider = 0U;
            USART1_SendString((recording != 0U) ? "RECORD ON\r\n" : "RECORD OFF\r\n");
            while (Button_IsPressed(BUTTON_RECORD_PIN) != 0U) { }
            Delay_ms(30U);
        }
    }

    if (Button_IsPressed(BUTTON_DUMP_PIN) != 0U)
    {
        Delay_ms(30U);
        if (Button_IsPressed(BUTTON_DUMP_PIN) != 0U)
        {
            press_tick = system_ticks_10ms;
            erased = 0U;

            while (Button_IsPressed(BUTTON_DUMP_PIN) != 0U)
            {
                if (((system_ticks_10ms - press_tick) >= BUTTON_HOLD_TICKS) && (erased == 0U))
                {
                    erased = 1U;
                    Recorder_EraseAll();
                }
            }

            Delay_ms(30U);
            if (erased == 0U) { Recorder_DumpText(); }
        }
    }

    GPIO_WritePin(GPIOB, LED_GREEN_PIN, recording);
}

/* ===================== Main ===================== */
int main(void)
{
    MpuSample_TypeDef sample;

    Clock_Init_72MHz_HSE8();
    GPIO_Init();
    USART1_Init();
    I2C1_Init();
    SPI1_Init();
    W25_ClearProtection();
    MPU6050_Init();
    TIM2_Init();

    USART1_SendString("START\r\n");

    while (1)
    {
        Buttons_Task();

        if ((recording != 0U) && (sample_flag != 0U))
        {
            sample_flag = 0U;

            MPU6050_ReadSample(&sample);
            Text_BuildSample(&sample);
            USART1_SendString(sample_text);
            Recorder_WriteLog(sample_text, sample_text_len);
            if (recording != 0U) { sample_count++; }
        }
    }
}
