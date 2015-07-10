package us.hiku.sdk.test;

import us.hiku.android.sdk.ApplicationAuthorizationHandler;
import us.hiku.android.sdk.DeviceSetupHandler;
import us.hiku.android.sdk.HikuSetupSDK;
import us.hiku.android.sdk.TutorialCompletedHandler;
import us.hiku.android.sdk.UserAuthenticationHandler;
import us.hiku.android.sdk.UserCancelledSetupHandler;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.provider.Settings;
import android.util.Log;
import android.util.TypedValue;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

import java.util.Arrays;
import java.util.Locale;

public class MainActivity extends Activity {

    private static final String APP_ID = "<yourAppId>";
    private static final String APP_SECRET = "<yourAppSecret>";

    private static final String TAG = "MainActivity";

    private HikuSetupSDK mSdk;
    private String mEmail;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_ACTION_BAR);
        setContentView(R.layout.activity_main);

        mSdk = HikuSetupSDK.getInstance(this);
        mSdk.setAppId(APP_ID);
        mSdk.setAppSecret(APP_SECRET);

        String[] mLanguageTitles = getResources().getStringArray(R.array.language_array);
        final String[] mLanguageCodes = getResources().getStringArray(R.array.language_codes);

        Spinner dropdown = (Spinner)findViewById(R.id.spinner1);
        final ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, mLanguageTitles);
        dropdown.setAdapter(adapter);
        //adapter.setDropDownViewResource(android.R.layout.simple_spinner_item);

        final Locale current = getResources().getConfiguration().locale;
        final String lang = current.getLanguage() + "-" + current.getCountry();
        int defaultSelection = Arrays.asList(mLanguageCodes).indexOf(lang);
        if (defaultSelection==-1)
            defaultSelection = Arrays.asList(mLanguageCodes).indexOf(current.getLanguage());
        dropdown.setSelection(defaultSelection);

        dropdown.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parentView, View selectedItemView, int position, long id) {
                String languageCode = mLanguageCodes[position];
                String msg = String.format("%s %s %s", lang, languageCode, adapter.getItem(position));
                Toast.makeText(getApplicationContext(),msg,Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onNothingSelected(AdapterView<?> parentView) {
                // your code here
            }

        });

        float density = getResources().getDisplayMetrics().density;
        float maxSize = 640.0F * density;
        Log.d(TAG, "density: " + density);
        Log.d(TAG, "maxSize: " + maxSize);
        TextView debug = (TextView) findViewById(R.id.debug);
        int height = getResources().getDisplayMetrics().heightPixels;
        String msg = String.format("density: %f \nmaxSize: %f\nheight: %d", density, maxSize, height);
        debug.setText(msg);

        if (height>maxSize) {
            // Calculate ActionBar height
            TypedValue tv = new TypedValue();
            int actionBarHeight = 0 ;
            if (getTheme().resolveAttribute(android.R.attr.actionBarSize, tv, true))
            {
                actionBarHeight = TypedValue.complexToDimensionPixelSize(tv.data,getResources().getDisplayMetrics());
            }


            int offset = (int) ((((float)height - maxSize ) / 2) - actionBarHeight);
            EditText t1 = ((EditText) findViewById(R.id.email));
            t1.setPadding(0, offset, 0, 0);
        }

        TextView debug2 = (TextView) findViewById(R.id.debug2);
        final float defaultBrightness = getBrightnessLevel();
        final Boolean defaultMode = getAutoBrightness();

        String brightnessDetails = String.format("defaultBrightness: %f\nautoBrightness: %b ", defaultBrightness, defaultMode);
        debug2.setText(brightnessDetails);

        final ToggleButton brightButton  = (ToggleButton) findViewById(R.id.bright);
        brightButton.setChecked(false);

        brightButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Boolean b = brightButton.isChecked();

                if (b) {
                    Toast.makeText(getActivity(), "Blinkup mode",Toast.LENGTH_SHORT).show();
                    setAutoBrightness(false);
                    refreshBrightness(1.0f);
                } else {
                    Toast.makeText(getActivity(), "Default",Toast.LENGTH_SHORT).show();
                    setAutoBrightness(defaultMode);
                    refreshBrightness(defaultBrightness);
                }


            }
        });

    }

    public void startSetup(View v) {

        String email = ((EditText) findViewById(R.id.email)).getText()
                .toString();

        if (!email.equals("")) {
            mEmail = email;
            mSdk.setEmail(mEmail);
        }
        else {
            mEmail = null;
            mSdk.setEmail(mEmail);
        }



        mSdk.startSetup(this, authorizationHandler, setupHandler,
                authenticationHandler, cancelHandler, tutorialCompletedHandler);
    }

    public void clear(View v) {
        ((EditText) findViewById(R.id.email)).setText("");
    }
    public void nextActivity(View v) {
        Intent i = new Intent(this, SampleActivity.class   );
        startActivity(i);
    }

    public void launchOrientation(View v) {
        if (mSdk.getUserAuthenticationStatus())
            mSdk.launchOrientation(this);
        else
            Toast.makeText(this,"User must be logged in", Toast.LENGTH_SHORT).show();
    }

    public void logoutUser(View v) {
        mSdk.logoutUser(this);
    }

    private TutorialCompletedHandler tutorialCompletedHandler = new TutorialCompletedHandler() {
        @Override
        public void onCompletion() {
            String msg = String.format("User completed tutorial!");
            Toast.makeText(MainActivity.this, msg, Toast.LENGTH_SHORT).show();
        }
    };

    private UserCancelledSetupHandler cancelHandler = new UserCancelledSetupHandler() {
        @Override
        public void onCancel() {
            String msg = String.format("User cancelled setup!");
            Toast.makeText(MainActivity.this, msg, Toast.LENGTH_SHORT).show();
        }
    };

    private ApplicationAuthorizationHandler authorizationHandler = new ApplicationAuthorizationHandler() {
        @Override
        public void onAuthorization(boolean authorized) {
            String msg = String.format("Application authorization status: %b",
                    authorized);
            Toast.makeText(MainActivity.this, msg, Toast.LENGTH_SHORT).show();
        }
    };

    private UserAuthenticationHandler authenticationHandler = new UserAuthenticationHandler() {
        @Override
        public void onAuthentication(boolean authenticated) {
            String msg = String.format("User authentication status: %b",
                    authenticated);
            Log.d(TAG, msg);
            Toast.makeText(MainActivity.this, msg, Toast.LENGTH_SHORT).show();
        }
    };

    private DeviceSetupHandler setupHandler = new DeviceSetupHandler() {
        @Override
        public void onResult(boolean success) {
            String msg = String.format("Device Setup Status: %b", success);
            Toast.makeText(MainActivity.this, msg, Toast.LENGTH_SHORT).show();
        }
    };


    protected void setAutoBrightness(boolean value) {

        Activity activity = getActivity();
        if (value) {
            Settings.System.putInt(activity.getContentResolver(), Settings.System.SCREEN_BRIGHTNESS_MODE, Settings.System.SCREEN_BRIGHTNESS_MODE_AUTOMATIC);
        } else {
            Settings.System.putInt(activity.getContentResolver(), Settings.System.SCREEN_BRIGHTNESS_MODE, Settings.System.SCREEN_BRIGHTNESS_MODE_MANUAL);
        }

    }

    protected Boolean getAutoBrightness() {
        try {
            // 1 = ON, 0=OFF
            int value = Settings.System.getInt(getActivity().getContentResolver(), Settings.System.SCREEN_BRIGHTNESS_MODE);
            return value==1;
        } catch (Settings.SettingNotFoundException e) {
            return Boolean.FALSE;
        }
    }

    protected void refreshBrightness(float brightness) {
        WindowManager.LayoutParams lp = getActivity().getWindow().getAttributes();
        if (brightness < 0) {
            lp.screenBrightness = WindowManager.LayoutParams.BRIGHTNESS_OVERRIDE_NONE;
        } else {
            lp.screenBrightness = brightness;
        }
        getActivity().getWindow().setAttributes(lp);
    }

    protected Float getBrightnessLevel() {
        try {
            // brightness value is between 0...255
            int value = Settings.System.getInt(getActivity().getContentResolver(), Settings.System.SCREEN_BRIGHTNESS);
            // convert brightness level to range 0..1
            return (float) (value / 255.0);
        } catch (Settings.SettingNotFoundException e) {
            return 0.0f;
        }
    }

    Activity getActivity() {
        return this;
    }
}
