<script>
    import moment from "moment"

    export let productCode

    function getSoftwareVersion() {
        return productCode.substring(0, 3);
    }

    function getKeypadType() {
        const keyPadTypes = {
            "B": "Binary",
            "M": "Morse",
            "N": "None"
        }

        const keypadCode = productCode.substring(3, 4);

        if (keyPadTypes[keypadCode] === undefined) {
            return "?";
        }

        return keyPadTypes[keypadCode];
    }

    function getHardwareRevision() {
        const hardwareRevisionCode = productCode.substring(5, 6);

        const hardwareRevision = hardwareRevisionCode.toUpperCase().charCodeAt(0) - "A".charCodeAt(0);

        var wiredRevisionCodes = /^[a-z]+$/;
        const isWired = (hardwareRevisionCode.match(wiredRevisionCodes));

        return hardwareRevisionCode + (isWired ? " (wired)" : "");
    }

    function getManufacturingMonth() {
        const monthCode = productCode.substring(6, 7);

        const monthNumber = parseInt("0x" + monthCode) - 1;

        return moment().month(monthNumber).format("MMM");
    }

    function getManufacturingYear() {
        const yearCode = parseInt(productCode.substring(7, 8));

        return 2020 + yearCode;
    }

    function getSecureBootloader() {
        const futherOptionsCodes = productCode.substring(9);

        return futherOptionsCodes.indexOf("S") !== -1;
    }
</script>

<div class="productCodeDisplay">
    <div class="productCode">
        {productCode}
    </div>

    <div>
        SW Version
    </div>
    <div>
        {getSoftwareVersion()}
    </div>

    <div>
        Keypad Type
    </div>
    <div>
        {getKeypadType()}
    </div>

    <div>
        HW Revision
    </div>
    <div>
        {getHardwareRevision()}
    </div>

    <div>
        Manufacturing Date
    </div>
    <div>
        {getManufacturingMonth()} {getManufacturingYear()}
    </div>

    <div>
        Secure Bootloader
    </div>
    <div>
        {getSecureBootloader() ? "Yes" : "No"}
    </div>

</div>

<style>
    .productCodeDisplay {
        display: grid;
        grid-template-columns: 200px 400px;
        grid-template-rows: 1fr 1fr 1fr 1fr 1fr 1fr;
        gap: 0px 0px;
        grid-template-areas:
    "productCode productCode"
    ". . "
    ". . "
    ". . "
    ". . "
    ". . ";
    }

    .productCode {
        grid-area: productCode;
        text-align: center;
        font-weight: bold;
    }
</style>